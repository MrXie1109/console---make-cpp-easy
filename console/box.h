#pragma once
#include <vector>
#include <typeinfo>
#include <utility>
#include "strpp.h"
#include "csexc.h"

namespace console
{
    using namespace std;

    class Item
    {
    private:
        struct Base
        {
            virtual ~Base() {}
            virtual Base *clone() const = 0;
            virtual const type_info &type() const = 0;
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
            const type_info &type() const
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
        template <typename T>
        T &get()
        {
            if (ptr == nullptr)
                throw bad_get("empty item");
            if (typeid(T) != ptr->type())
                throw bad_get("type mismatch: "s +
                              typeid(T).name() +
                              " and " +
                              ptr->type().name());
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
        ~Item() { delete ptr; }
    };

    class Box : public vector<Item>
    {
    public:
        template <class... Args>
        Box(Args &&...args) : vector<Item>({Item(forward<Args>(args))...}) {}
        template <class T>
        T &get(size_t index)
        {
            return vector<Item>::at(index).get<T>();
        }
        template <class... Args>
        void unpack(Args &&...args)
        {
            size_t i = 0;
            int _[] = {0, ((args = get<Args>(i++)), 0)...};
            (void)_;
        }
    };
}
