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
#include <cstddef>
#include <vector>
#include <array>
#include <utility>
#include <map>
#include <set>
#include <deque>
#include <list>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <valarray>

namespace console
{
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::vector<T> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::deque<T> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::list<T> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::forward_list<T> &);
    template <class T, size_t n>
    std::ostream &operator<<(std::ostream &, const std::array<T, n> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::set<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::map<K, V> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::multiset<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::multimap<K, V> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::unordered_set<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::unordered_map<K, V> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::unordered_multiset<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::unordered_multimap<K, V> &);
    template <class T, class U>
    std::ostream &operator<<(std::ostream &, const std::pair<T, U> &);
    template <class... Args>
    std::ostream &operator<<(std::ostream &, const std::tuple<Args...> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::valarray<T> &);

    template <class Cont>
    std::ostream &cont_print_sequence(std::ostream &os, const Cont &cont)
    {
        if (begin(cont) == end(cont))
            return os << "[]";
        auto it = begin(cont);
        os << '[' << *it;
        while (++it != end(cont))
        {
            os << ", " << *it;
        }
        return os << ']';
    }

    template <class Cont>
    std::ostream &cont_print_set(std::ostream &os, const Cont &cont)
    {
        if (begin(cont) == end(cont))
            return os << "{}";
        auto it = begin(cont);
        os << '{' << *it;
        while (++it != end(cont))
        {
            os << ", " << *it;
        }
        return os << '}';
    }

    template <class Cont>
    std::ostream &cont_print_map(std::ostream &os, const Cont &cont)
    {
        if (begin(cont) == end(cont))
            return os << "{}";
        auto it = begin(cont);
        os << '{' << it->first << ": " << it->second;
        while (++it != end(cont))
        {
            os << ", " << it->first << ": " << it->second;
        }
        return os << '}';
    }

    template <class Tuple, size_t N = std::tuple_size<Tuple>::value>
    struct TuplePrinter
    {
        static void print(std::ostream &os, const Tuple &t)
        {
            TuplePrinter<Tuple, N - 1>::print(os, t);
            if (N > 1)
                os << ", ";
            os << std::get<N - 1>(t);
        }
    };

    template <class Tuple>
    struct TuplePrinter<Tuple, 1>
    {
        static void print(std::ostream &os, const Tuple &t)
        {
            os << std::get<0>(t);
        }
    };

    template <class Tuple>
    struct TuplePrinter<Tuple, 0>
    {
        static void print(std::ostream &os, const Tuple &t) {}
    };

    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
    {
        return cont_print_sequence(os, vec);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::deque<T> &deq)
    {
        return cont_print_sequence(os, deq);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::list<T> &lst)
    {
        return cont_print_sequence(os, lst);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::forward_list<T> &flst)
    {
        return cont_print_sequence(os, flst);
    }
    template <class T, size_t n>
    std::ostream &operator<<(std::ostream &os, const std::array<T, n> &arr)
    {
        return cont_print_sequence(os, arr);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::set<T> &s)
    {
        return cont_print_set(os, s);
    }
    template <class K, class V>
    std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m)
    {
        return cont_print_map(os, m);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::multiset<T> &ms)
    {
        return cont_print_set(os, ms);
    }
    template <class K, class V>
    std::ostream &operator<<(std::ostream &os, const std::multimap<K, V> &mm)
    {
        return cont_print_map(os, mm);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &us)
    {
        return cont_print_set(os, us);
    }
    template <class K, class V>
    std::ostream &operator<<(std::ostream &os,
                             const std::unordered_map<K, V> &um)
    {
        return cont_print_map(os, um);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os,
                             const std::unordered_multiset<T> &ums)
    {
        return cont_print_set(os, ums);
    }
    template <class K, class V>
    std::ostream &operator<<(std::ostream &os,
                             const std::unordered_multimap<K, V> &ump)
    {
        return cont_print_map(os, ump);
    }
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::valarray<T> &va)
    {
        return cont_print_sequence(os, va);
    }
    template <class T, class U>
    std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p)
    {
        return os << '(' << p.first << ", " << p.second << ')';
    }
    template <class... Args>
    std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &t)
    {
        os << "(";
        TuplePrinter<std::tuple<Args...>>::print(os, t);
        return os << ")";
    }

    template <class T, size_t N>
    std::array<T, N> to_array(const T (&ar)[N])
    {
        std::array<T, N> arr;
        std::copy(ar, ar + N, arr.begin());
        return arr;
    }

    template <class T, size_t N>
    std::vector<T> to_vector(const T (&ar)[N])
    {
        std::vector<T> vec(N);
        std::copy(ar, ar + N, vec.begin());
        return vec;
    }

    class Output
    {
        std::ostream &os;
        std::string sep;
        std::string end;
        bool isFlush;

    public:
        Output() : os(std::cout), sep(" "), end("\n"), isFlush(true) {}
        Output(std::ostream &o, const std::string &s, const std::string &e, bool isF)
            : os(o), sep(s), end(e), isFlush(isF) {}

        void operator()()
        {
            os << end;
            if (isFlush)
                os << std::flush;
        }
        template <class T>
        void operator()(const T &t)
        {
            os << t;
            operator()();
        }
        template <class T, class... Args>
        void operator()(const T &t, const Args &...args)
        {
            os << t << sep;
            operator()(args...);
        }
    } print;
}
