#pragma once
#include <iostream>
#include <cstddef>
#include <vector>
#include <array>
#include <utility>
#include <map>
#include <set>

namespace console
{
    using namespace std;

    template <class T>
    ostream &operator<<(ostream &, const vector<T> &);
    template <class T, size_t n>
    ostream &operator<<(ostream &, const array<T, n> &);
    template <class T, class U>
    ostream &operator<<(ostream &, const pair<T, U> &);
    template <class K, class V>
    ostream &operator<<(ostream &, const map<K, V> &);
    template <class T>
    ostream &operator<<(ostream &, const set<T> &);

    /**
     * 为各种常见STL容器定义便捷的输出方式
     * 支持的类型：
     * std::vector
     * std::array
     * std::pair
     * std::map
     * std::set
     * 注意：C风格数组因兼容性不兼容，
     *      可以先使用console::to_array()或console::to_vector()转化
     */

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

    template <class T>
    ostream &operator<<(ostream &os, const vector<T> &vec)
    {
        if (vec.empty())
            return os << "[]";
        auto it = vec.begin();
        os << '[' << *it;
        while (++it != vec.end())
        {
            os << ", " << *it;
        }
        return os << ']';
    }

    template <class T, size_t N>
    ostream &operator<<(ostream &os, const array<T, N> &ar)
    {
        if (ar.empty())
            return os << "[]";
        auto it = ar.begin();
        os << '[' << *it;
        while (++it != ar.end())
        {
            os << ", " << *it;
        }
        return os << ']';
    }

    template <class T, class U>
    ostream &operator<<(ostream &os, const pair<T, U> &p)
    {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template <class K, class V>
    ostream &operator<<(ostream &os, const map<K, V> &m)
    {
        if (m.empty())
            return os << "{}";
        auto it = m.begin();
        os << '{' << it->first << ": " << it->second;
        while (++it != m.end())
        {
            os << ", " << it->first << ": " << it->second;
        }
        return os << '}';
    }

    template <class T>
    ostream &operator<<(ostream &os, const set<T> &s)
    {
        if (s.empty())
            return os << "{}";
        auto it = s.begin();
        os << '{' << *it;
        while (++it != s.end())
        {
            os << ", " << *it;
        }
        return os << '}';
    }

    /**
     * 一个类似Python但没有Python好用的输出方式
     * （至少比std::printf和std::cout好）
     * 接口：
     * console::Output output(输出流, 间隔符, 结束符, 是否刷新);
     * //默认的print设置为std::cout/" "/"\n"/true
     * print("你好", 123, "世界");
     * 输出示例：
     * ---
     * 你好 123 世界
     *
     * ---
     */

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