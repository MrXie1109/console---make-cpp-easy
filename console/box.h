/*

Copyright (c) 2026 MrXie1109

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once
#include <vector>
#include <typeinfo>
#include <utility>
#include <ostream>
#include <memory>
#include <cstdlib>
#include "strpp.h"
#include "csexc.h"
#include "literals.h"
#ifdef __GNUG__
#include <cxxabi.h>
#endif

namespace console
{
    std::string tiname(const std::type_info &ti)
    {
#ifdef _MSC_VER
        return ti.name();
#elif defined(__GNUG__)
        int status = 0;
        std::unique_ptr<char, void (*)(void *)> result(
            abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status),
            std::free);
        return (status == 0) ? result.get() : ti.name();
#else
        return ti.name();
#endif
    }

    class Item
    {
    private:
        struct Base
        {
            virtual ~Base() {}
            virtual Base *clone() const = 0;
            virtual void print(std::ostream &) const = 0;
            virtual std::string str() const = 0;
            virtual const std::type_info &type() const = 0;
        };
        template <typename T>
        struct Derived : Base
        {
            T value;
            Derived(const T &v) : value(v) {}
            Base *clone() const
            {
                return new Derived(value);
            }
            void print(std::ostream &os) const
            {
                os << value;
            }
            std::string str() const
            {
                return uniToStr(value);
            }
            const std::type_info &type() const
            {
                return typeid(T);
            }
        };
        Base *ptr;

    public:
        Item() : ptr(nullptr) {}
        template <typename T>
        Item(const T &value)
            : ptr(new Derived<T>(value)) {}
        Item(const Item &other)
            : ptr(other.ptr ? other.ptr->clone() : nullptr) {}
        Item(Item &&other) noexcept : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }
        template <size_t N>
        Item(const char (&str)[N])
            : ptr(new Derived<const char *>((const char *)str)) {}
        template <typename T>
        T &get()
        {
            using namespace console::literals;
            if (ptr == nullptr)
                throw bad_get("empty item");
            if (typeid(T) != ptr->type())
                throw bad_get("type mismatch: "s +
                              tiname(typeid(T)) +
                              " and " +
                              tiname(ptr->type()));
            return ((Derived<T> *)ptr)->value;
        }
        template <typename T>
        T &unsafe_get()
        {
            return ((Derived<T> *)ptr)->value;
        }
        template <typename T>
        const T &get() const
        {
            using namespace console::literals;
            if (ptr == nullptr)
                throw bad_get("empty item");
            if (typeid(T) != ptr->type())
                throw bad_get("type mismatch: "s +
                              typeid(T).name() +
                              " and " +
                              ptr->type().name());
            return ((Derived<T> *)ptr)->value;
        }
        template <typename T>
        const T &unsafe_get() const
        {
            return ((Derived<T> *)ptr)->value;
        }
        Item &operator=(const Item &other)
        {
            if (this != &other)
            {
                Base *new_ptr = other.ptr ? other.ptr->clone() : nullptr;
                delete ptr;
                ptr = new_ptr;
            }
            return *this;
        }
        Item &operator=(Item &&other) noexcept
        {
            if (this != &other)
            {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &os, const Item &item)
        {
            item.ptr->print(os);
            return os;
        }
        std::string str() const
        {
            return ptr->str();
        }
        ~Item() { delete ptr; }
    };

    class Box : public std::vector<Item>
    {
    public:
        template <class... Args>
        Box(Args &&...args)
            : std::vector<Item>({Item(std::forward<Args>(args))...}) {}
        template <class T>
        T &get(size_t index)
        {
            return std::vector<Item>::at(index).get<T>();
        }
        template <typename T>
        T &unsafe_get(size_t index)
        {
            return std::vector<Item>::operator[](index).unsafe_get<T>();
        }
        template <class... Args>
        void unpack(Args &...args)
        {
            size_t i = 0;
            int _[] = {0, ((args = get<Args>(i++)), 0)...};
            (void)_;
        }
        template <class... Args>
        void unsafe_unpack(Args &...args)
        {
            size_t i = 0;
            int _[] = {0, ((args = unsafe_get<Args>(i++)), 0)...};
            (void)_;
        }
        friend std::ostream &operator<<(std::ostream &os, const Box &box)
        {
            if (box.empty())
                return os << "()";
            auto it = box.begin();
            os << '(' << *it;
            while (++it != box.end())
                os << ", " << *it;
            return os << ')';
        }
    };
}
