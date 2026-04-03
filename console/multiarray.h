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
#include <iostream>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include "csexc.h"
#include "repr.h"

namespace console
{
    template <class T, size_t... Dims>
    class MultiArray;

    template <class T, size_t D>
    class MultiArray<T, D> : public std::array<T, D>
    {
        using base_type = std::array<T, D>;

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;

        MultiArray() = default;

        explicit MultiArray(const T &value)
        {
            fill(value);
        }

        MultiArray(const base_type &other) : base_type(other) {}

        MultiArray(std::initializer_list<T> init) : base_type(init) {}

        static constexpr size_t rank() { return 1; }
        static constexpr size_t size() { return D; }

        void fill(const T &value)
        {
            for (auto &item : *this)
                item = value;
        }

        template <class F>
        void for_each(F &&visit)
        {
            for (auto &item : *this)
                visit(item);
        }

        template <class F>
        void for_each(F &&visit) const
        {
            for (const auto &item : *this)
                visit(item);
        }

        reference at(size_t i)
        {
            if (i >= D)
                throw multiarray_error(
                    "index " +
                    std::to_string(i) +
                    " out of range [0, " +
                    std::to_string(D) +
                    ')');
            return (*this)[i];
        }

        const_reference at(size_t i) const
        {
            if (i >= D)
                throw multiarray_error(
                    "index " +
                    std::to_string(i) +
                    " out of range [0, " +
                    std::to_string(D) +
                    ')');
            return (*this)[i];
        }

        reference operator()(size_t i)
        {
            return at(i);
        }

        const_reference operator()(size_t i) const
        {
            return at(i);
        }

        friend std::ostream &operator<<(std::ostream &os, const MultiArray &ma)
        {
            if (ma.begin() == ma.end())
                return os << "[]";
            auto it = ma.begin();
            os << '[';
            repr(*it, os);
            while (++it != ma.end())
            {
                os << ", ";
                repr(*it, os);
            }
            return os << ']';
        }

        T *fbegin() { return this->data(); } // flatten
        const T *fbegin() const { return this->data(); }

        T *fend() { return this->data() + size(); }
        const T *fend() const { return this->data() + size(); }
    };

    template <class T, size_t First, size_t... Rest>
    class MultiArray<T, First, Rest...>
        : public std::array<MultiArray<T, Rest...>, First>
    {
        using base_type = std::array<MultiArray<T, Rest...>, First>;

    public:
        using value_type = T;
        using reference = MultiArray<T, Rest...> &;
        using const_reference = const MultiArray<T, Rest...> &;

        MultiArray() = default;

        explicit MultiArray(const T &value)
        {
            fill(value);
        }

        MultiArray(std::initializer_list<MultiArray<T, Rest...>> init)
            : base_type(init) {}

        static constexpr size_t rank() { return 1 + sizeof...(Rest); }

        static constexpr size_t size()
        {
            return First * MultiArray<T, Rest...>::size();
        }

        void fill(const T &value)
        {
            for (auto &sub : *this)
                sub.fill(value);
        }

        template <class F>
        void for_each(F &&visit)
        {
            for (auto &sub : *this)
                sub.for_each(visit);
        }

        template <class F>
        void for_each(F &&visit) const
        {
            for (const auto &sub : *this)
                sub.for_each(visit);
        }

        template <class... Indices>
        typename std::enable_if<sizeof...(Indices) + 1 == rank(), T &>::type
        at(size_t idx, Indices... rest)
        {
            if (idx >= First)
                throw multiarray_error(
                    "index " +
                    std::to_string(idx) +
                    " out of range [0, " +
                    std::to_string(First) +
                    ')');
            return base_type::operator[](idx).at(rest...);
        }

        template <class... Indices>
        typename std::enable_if<sizeof...(Indices) + 1 == rank(), const T &>::type
        at(size_t idx, Indices... rest) const
        {
            if (idx >= First)
                throw multiarray_error(
                    "index " +
                    std::to_string(idx) +
                    " out of range [0, " +
                    std::to_string(First) +
                    ')');
            return base_type::operator[](idx).at(rest...);
        }

        template <class... Indices>
        T &operator()(Indices... indices)
        {
            return at(indices...);
        }

        template <class... Indices>
        const T &operator()(Indices... indices) const
        {
            return at(indices...);
        }

        friend std::ostream &operator<<(std::ostream &os, const MultiArray &ma)
        {
            if (ma.begin() == ma.end())
                return os << "[]";
            auto it = ma.begin();
            os << '[' << *it;
            while (++it != ma.end())
            {
                os << ", " << *it;
            }
            return os << ']';
        }

        T *fbegin() { return this->data()->fbegin(); }
        const T *fbegin() const { return this->data()->fbegin(); }

        T *fend() { return (*this)[First - 1].fend(); }
        const T *fend() const { return (*this)[First - 1].fend(); }
    };

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator+(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ + *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator-(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ - *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator*(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ * *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator/(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ / *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator%(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ % *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator+=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ += *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator-=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ -= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator*=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ *= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator/=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ /= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator%=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ %= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator==(const MultiArray<T, Dims...> &a,
                                         const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ == *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator!=(const MultiArray<T, Dims...> &a,
                                         const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ != *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator<(const MultiArray<T, Dims...> &a,
                                        const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ < *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator>(const MultiArray<T, Dims...> &a,
                                        const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ > *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator<=(const MultiArray<T, Dims...> &a,
                                         const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ <= *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator>=(const MultiArray<T, Dims...> &a,
                                         const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ >= *bi++;
        return c;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator+(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ + value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator-(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ - value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator*(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ * value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator/(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ / value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator%(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ % value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator+=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref += value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator-=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref -= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator*=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref *= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator/=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref /= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator%=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref %= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator+(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        return a + value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator-(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = value - *ai++;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator*(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        return a * value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator/(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = value / *ai++;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator%(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = value % *ai++;
        return b;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator+(const MultiArray<T, Dims...> &a)
    {
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator-(const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = -*ai++;
        return b;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator!(const MultiArray<T, Dims...> &a)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = !*ai++;
        return b;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator~(const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = ~*ai++;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator==(const MultiArray<T, Dims...> &a,
                                         const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ == value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator!=(const MultiArray<T, Dims...> &a,
                                         const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ != value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator<(const MultiArray<T, Dims...> &a,
                                        const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ < value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator>(const MultiArray<T, Dims...> &a,
                                        const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ > value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator<=(const MultiArray<T, Dims...> &a,
                                         const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ <= value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator>=(const MultiArray<T, Dims...> &a,
                                         const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ >= value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator==(const U &value,
                                         const MultiArray<T, Dims...> &a)
    {
        return a == value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator!=(const U &value,
                                         const MultiArray<T, Dims...> &a)
    {
        return a != value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator<(const U &value,
                                        const MultiArray<T, Dims...> &a)
    {
        return a < value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator>(const U &value,
                                        const MultiArray<T, Dims...> &a)
    {
        return a > value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator<=(const U &value,
                                         const MultiArray<T, Dims...> &a)
    {
        return a <= value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator>=(const U &value,
                                         const MultiArray<T, Dims...> &a)
    {
        return a >= value;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator&(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ & *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator|(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ | *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator^(const MultiArray<T, Dims...> &a,
                                     const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ ^ *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator&=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ &= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator|=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ |= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> &operator^=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ ^= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator<<(const MultiArray<T, Dims...> &a,
                                      const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ << *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator>>(const MultiArray<T, Dims...> &a,
                                      const MultiArray<T, Dims...> &b)
    {
        MultiArray<T, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ >> *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator<<=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ <<= *bi++;
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> operator>>=(MultiArray<T, Dims...> &a,
                                       const MultiArray<T, Dims...> &b)
    {
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            *ai++ >>= *bi++;
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator&(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ & value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator|(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ | value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator^(const MultiArray<T, Dims...> &a,
                                     const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ ^ value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator<<(const MultiArray<T, Dims...> &a,
                                      const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ << value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator>>(const MultiArray<T, Dims...> &a,
                                      const U &value)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ >> value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator&(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        return a & value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator|(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        return a | value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator^(const U &value,
                                     const MultiArray<T, Dims...> &a)
    {
        return a ^ value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator<<(const U &value,
                                      const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = value << *ai++;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> operator>>(const U &value,
                                      const MultiArray<T, Dims...> &a)
    {
        MultiArray<T, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = value >> *ai++;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator&=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref &= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator|=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref |= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator^=(const MultiArray<T, Dims...> &a,
                                       const U &value)
    {
        a.for_each([](T &ref)
                   { ref ^= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator<<=(const MultiArray<T, Dims...> &a,
                                        const U &value)
    {
        a.for_each([](T &ref)
                   { ref <<= value; });
        return a;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<T, Dims...> &operator>>=(const MultiArray<T, Dims...> &a,
                                        const U &value)
    {
        a.for_each([](T &ref)
                   { ref >>= value; });
        return a;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator&&(const MultiArray<T, Dims...> &a,
                                         const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ && *bi++;
        return c;
    }

    template <class T, size_t... Dims>
    MultiArray<bool, Dims...> operator||(const MultiArray<T, Dims...> &a,
                                         const MultiArray<T, Dims...> &b)
    {
        MultiArray<bool, Dims...> c;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        auto ci = c.fbegin();
        while (ci != c.fend())
            *ci++ = *ai++ || *bi++;
        return c;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator&&(const MultiArray<T, Dims...> &a,
                                         const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ && value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator||(const MultiArray<T, Dims...> &a,
                                         const U &value)
    {
        MultiArray<bool, Dims...> b;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (bi != b.fend())
            *bi++ = *ai++ || value;
        return b;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator&&(const U &value,
                                         const MultiArray<T, Dims...> &a)
    {
        return a && value;
    }

    template <class T, size_t... Dims, class U>
    MultiArray<bool, Dims...> operator||(const U &value,
                                         const MultiArray<T, Dims...> &a)
    {
        return a || value;
    }

    template <class T, size_t... Dims>
    T sum(const MultiArray<T, Dims...> &a)
    {
        T result{};
        a.for_each([&](const T &ref)
                   { result += ref; });
        return result;
    }

    template <class T, size_t... Dims>
    T min(const MultiArray<T, Dims...> &a)
    {
        return *std::min_element(a.fbegin(), a.fend());
    }

    template <class T, size_t... Dims>
    T max(const MultiArray<T, Dims...> &a)
    {
        return *std::max_element(a.fbegin(), a.fend());
    }

    template <class T, size_t... Dims>
    bool all(const MultiArray<T, Dims...> &a)
    {
        for (auto it = a.fbegin(); it != a.fend(); ++it)
            if (!*it)
                return false;
        return true;
    }

    template <class T, size_t... Dims>
    bool any(const MultiArray<T, Dims...> &a)
    {
        for (auto it = a.fbegin(); it != a.fend(); ++it)
            if (*it)
                return true;
        return false;
    }
}
