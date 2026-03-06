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
    using namespace std;

    template <class T>
    ostream &operator<<(ostream &, const vector<T> &);
    template <class T>
    ostream &operator<<(ostream &, const deque<T> &);
    template <class T>
    ostream &operator<<(ostream &, const list<T> &);
    template <class T>
    ostream &operator<<(ostream &, const forward_list<T> &);
    template <class T, size_t n>
    ostream &operator<<(ostream &, const array<T, n> &);
    template <class T>
    ostream &operator<<(ostream &, const set<T> &);
    template <class K, class V>
    ostream &operator<<(ostream &, const map<K, V> &);
    template <class T>
    ostream &operator<<(ostream &, const multiset<T> &);
    template <class K, class V>
    ostream &operator<<(ostream &, const multimap<K, V> &);
    template <class T>
    ostream &operator<<(ostream &, const unordered_set<T> &);
    template <class K, class V>
    ostream &operator<<(ostream &, const unordered_map<K, V> &);
    template <class T>
    ostream &operator<<(ostream &, const unordered_multiset<T> &);
    template <class K, class V>
    ostream &operator<<(ostream &, const unordered_multimap<K, V> &);
    template <class T, class U>
    ostream &operator<<(ostream &, const pair<T, U> &);
    template <class... Args>
    ostream &operator<<(ostream &, const tuple<Args...> &);
    template <class T>
    ostream &operator<<(ostream &, const valarray<T> &);

    template <class Cont>
    ostream &cont_print_sequence(ostream &os, const Cont &cont)
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
    ostream &cont_print_set(ostream &os, const Cont &cont)
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
    ostream &cont_print_map(ostream &os, const Cont &cont)
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

    template <class Tuple, size_t N = tuple_size<Tuple>::value>
    struct TuplePrinter
    {
        static void print(ostream &os, const Tuple &t)
        {
            TuplePrinter<Tuple, N - 1>::print(os, t);
            if (N > 1)
                os << ", ";
            os << get<N - 1>(t);
        }
    };

    template <class Tuple>
    struct TuplePrinter<Tuple, 1>
    {
        static void print(ostream &os, const Tuple &t) { os << get<0>(t); }
    };

    template <class Tuple>
    struct TuplePrinter<Tuple, 0>
    {
        static void print(ostream &os, const Tuple &t) {}
    };

    template <class T>
    ostream &operator<<(ostream &os, const vector<T> &vec)
    {
        return cont_print_sequence(os, vec);
    }
    template <class T>
    ostream &operator<<(ostream &os, const deque<T> &deq)
    {
        return cont_print_sequence(os, deq);
    }
    template <class T>
    ostream &operator<<(ostream &os, const list<T> &lst)
    {
        return cont_print_sequence(os, lst);
    }
    template <class T>
    ostream &operator<<(ostream &os, const forward_list<T> &flst)
    {
        return cont_print_sequence(os, flst);
    }
    template <class T, size_t n>
    ostream &operator<<(ostream &os, const array<T, n> &arr)
    {
        return cont_print_sequence(os, arr);
    }
    template <class T>
    ostream &operator<<(ostream &os, const set<T> &s)
    {
        return cont_print_set(os, s);
    }
    template <class K, class V>
    ostream &operator<<(ostream &os, const map<K, V> &m)
    {
        return cont_print_map(os, m);
    }
    template <class T>
    ostream &operator<<(ostream &os, const multiset<T> &ms)
    {
        return cont_print_set(os, ms);
    }
    template <class K, class V>
    ostream &operator<<(ostream &os, const multimap<K, V> &mm)
    {
        return cont_print_map(os, mm);
    }
    template <class T>
    ostream &operator<<(ostream &os, const unordered_set<T> &us)
    {
        return cont_print_set(os, us);
    }
    template <class K, class V>
    ostream &operator<<(ostream &os, const unordered_map<K, V> &um)
    {
        return cont_print_map(os, um);
    }
    template <class T>
    ostream &operator<<(ostream &os, const unordered_multiset<T> &ums)
    {
        return cont_print_set(os, ums);
    }
    template <class K, class V>
    ostream &operator<<(ostream &os, const unordered_multimap<K, V> &ump)
    {
        return cont_print_map(os, ump);
    }
    template <class T>
    ostream &operator<<(ostream &os, const valarray<T> va)
    {
        return cont_print_sequence(os, va);
    }
    template <class T, class U>
    ostream &operator<<(ostream &os, const pair<T, U> &p)
    {
        return os << '(' << p.first << ", " << p.second << ')';
    }
    template <class... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t)
    {
        os << "(";
        TuplePrinter<tuple<Args...>>::print(os, t);
        return os << ")";
    }

    template <class T, size_t N>
    array<T, N> to_array(const T (&ar)[N])
    {
        array<T, N> arr;
        copy(ar, ar + N, arr.begin());
        return arr;
    }

    template <class T, size_t N>
    vector<T> to_vector(const T (&ar)[N])
    {
        vector<T> vec(N);
        copy(ar, ar + N, vec.begin());
        return vec;
    }

    class Output
    {
        ostream &os;
        string sep;
        string end;
        bool isFlush;

    public:
        Output() : os(cout), sep(" "), end("\n"), isFlush(true) {}
        Output(ostream &o, const string &s, const string &e, bool isF)
            : os(o), sep(s), end(e), isFlush(isF) {}

        void operator()()
        {
            os << end;
            if (isFlush)
                os << flush;
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
