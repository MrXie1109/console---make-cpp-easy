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
#include <utility>
#include <memory>
#include <iostream>
#include "csexc.h"

namespace console
{
    struct
    {
    } nothing;

    template <class T>
    class Maybe
    {
        std::unique_ptr<T> ptr;

    public:
        Maybe() : ptr(nullptr) {}

        template <class... Args>
        Maybe(Args &&...args)
            : ptr(new T(std::forward<Args>(args)...)) {}

        Maybe(const Maybe &other)
            : ptr(other.ptr ? new T(other.value()) : nullptr) {}

        Maybe(Maybe &&other)
            : ptr(std::move(other.ptr)) {}

        Maybe(decltype(nothing)) : ptr(nullptr) {}

        T &value()
        {
            if (ptr)
                return *ptr;
            throw bad_maybe_access("Nothing");
        }

        const T &value() const
        {
            if (ptr)
                return *ptr;
            throw bad_maybe_access("Nothing");
        }

        const Maybe &operator=(const T &value)
        {
            ptr.reset(new T(value));
            return *this;
        }

        const Maybe &operator=(T &&value)
        {
            ptr.reset(new T(std::move(value)));
            return *this;
        }

        Maybe &operator=(const Maybe &other)
        {
            if (this != &other)
                ptr.reset(other.ptr ? new T(*other.ptr) : nullptr);
            return *this;
        }

        Maybe &operator=(Maybe &&other) noexcept
        {
            if (this != &other)
                ptr = std::move(other.ptr);
            return *this;
        }

        const Maybe &operator=(decltype(nothing))
        {
            ptr = nullptr;
            return *this;
        }

        void reset()
        {
            ptr.reset();
        }

        template <class... Args>
        void reset(Args &&...args)
        {
            ptr.reset(new T(std::forward<Args>(args)...));
        }

        friend std::ostream &operator<<(std::ostream &os, const Maybe &maybe)
        {
            if (maybe.ptr)
                return os << maybe.value();
            return os << "(nothing)";
        }

        friend std::istream &operator>>(std::istream &is, Maybe &maybe)
        {
            T tmp;
            if (is >> tmp)
                maybe.reset(std::move(tmp));
            else
            {
                maybe = nothing;
                is.clear();
            }
            return is;
        }

        explicit operator bool() const noexcept { return ptr; }
        bool has_value() const noexcept { return ptr; }

        T &operator*() { return *ptr; }
        const T &operator*() const { return *ptr; }
        T *operator->() { return ptr.get(); }
        const T *operator->() const { return ptr.get(); }

        template <class U>
        T value_or(U &&default_value) const
        {
            return ptr ? *ptr : T(std::forward<U>(default_value));
        }

        void swap(Maybe &other) noexcept
        {
            ptr.swap(other.ptr);
        }
    };
}
