#pragma once
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cfloat>
#include <climits>
#include <csetjmp>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#if __cplusplus >= 201103L
#include <cstdint>
#if __cplusplus < 201703L
#include <ciso646>
#endif
#endif
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <numeric>
#include <typeinfo>
#include <utility>
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <initializer_list>
#include <ratio>
#include <scoped_allocator>
#include <tuple>
#include <typeindex>
#include <type_traits>
#endif
#if __cplusplus >= 201402L
#endif
#if __cplusplus >= 201703L
#include <any>
#include <optional>
#include <variant>
#include <string_view>
#endif
#if __cplusplus >= 202002L
#include <bit>
#include <compare>
#include <concepts>
#include <numbers>
#include <ranges>
#include <span>
#include <source_location>
#include <version>
#if __cpp_impl_coroutine
#include <coroutine>
#endif
#endif
#if __cplusplus > 202002L
#include <expected>
#include <stdatomic.h>
#endif
#if _GLIBCXX_HOSTED
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#if __cplusplus >= 201103L
#include <cfenv>
#include <cinttypes>
#include <cstdint>
#include <cuchar>
#if __cplusplus < 201703L
#include <ccomplex>
#include <cstdalign>
#include <cstdbool>
#include <ctgmath>
#endif
#endif
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
#if __cplusplus >= 201402L
#include <shared_mutex>
#endif
#if __cplusplus >= 201703L
#include <any>
#include <charconv>
#include <filesystem>
#include <optional>
#include <memory_resource>
#include <variant>
#endif
#if __cplusplus >= 202002L
#include <barrier>
#include <bit>
#include <compare>
#include <concepts>
#include <format>
#include <latch>
#include <numbers>
#include <ranges>
#include <span>
#include <stop_token>
#include <semaphore>
#include <source_location>
#include <syncstream>
#include <version>
#endif
#if __cplusplus > 202002L
#include <expected>
#include <flat_map>
#include <flat_set>
#include <generator>
#include <print>
#include <spanstream>
#include <stacktrace>
#include <stdatomic.h>
#include <stdfloat>
#endif
#if __cplusplus > 202302L
#include <text_encoding>
#include <stdbit.h>
#include <stdckdint.h>
#endif
#endif

namespace console
{
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec);
    template <class T, size_t n>
    std::ostream &operator<<(std::ostream &os, const std::array<T, n> &ar);
    template <class T, class U>
    std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m);
    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::set<T> &s);

    template <class T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
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

    template <class T, size_t n>
    std::ostream &operator<<(std::ostream &os, const std::array<T, n> &ar)
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
    std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p)
    {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template <class K, class V>
    std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m)
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
    std::ostream &operator<<(std::ostream &os, const std::set<T> &s)
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

    class Output
    {
        std::ostream *os = &std::cout;
        std::string end = "\n";
        std::string sep = " ";

    public:
        Output(std::ostream &Os = std::cout,
               std::string End = "\n",
               std::string Sep = " ")
        {
            os = &Os;
            end = End;
            sep = Sep;
        }
        void set(std::ostream &Os = std::cout,
                 std::string End = "\n",
                 std::string Sep = " ")
        {
            os = &Os;
            end = End;
            sep = Sep;
        }
        void operator()()
        {
            (*os) << end;
        }
        template <class T>
        void operator()(const T &t)
        {
            (*os) << t << end;
        }
        template <class T, class... Args>
        void operator()(const T &t, const Args &...args)
        {
            (*os) << t << sep;
            operator()(args...);
        }
    } print, error(std::cerr);

    struct TimerResult
    {
        double ns, us, ms, s;
        operator double() const
        {
            return ns;
        }
        TimerResult operator+(const TimerResult &tr) const
        {
            return TimerResult{
                ns + tr.ns,
                us + tr.us,
                ms + tr.ms,
                s + tr.s};
        }
        TimerResult operator-(const TimerResult &tr) const
        {
            return TimerResult{
                ns - tr.ns,
                us - tr.us,
                ms - tr.ms,
                s - tr.s};
        }
        TimerResult operator*(double d) const
        {
            return TimerResult{
                ns * d,
                us * d,
                ms * d,
                s * d};
        }
        TimerResult operator/(double d) const
        {
            return TimerResult{
                ns / d,
                us / d,
                ms / d,
                s / d};
        }
        friend std::ostream &operator<<(std::ostream &os, const TimerResult tr)
        {
            if (tr.s >= 1)
                return os << tr.s << "  s";
            if (tr.ms >= 1)
                return os << tr.ms << " ms";
            if (tr.us >= 1)
                return os << tr.us << " μs";
            return os << tr.ns << " ns";
        }
    };

    template <class T>
    bool save(const T &data, const char *path)
    {
        std::ofstream file(path);
        if (!file)
            return false;
        file.write((const char *)(&data), sizeof(data));
        return file.good();
    }

    template <class T>
    bool load(T &data, const char *path)
    {
        std::ifstream file(path);
        if (!file)
            return false;
        file.read((char *)(&data), sizeof(data));
        return file.good();
    }

    std::string ltrim(std::string str)
    {
        auto it = std::find_if(str.begin(), str.end(),
                               [](unsigned char c)
                               { return !std::isspace(c); });
        str.erase(str.begin(), it);
        return str;
    }

    std::string rtrim(std::string str)
    {
        auto it = std::find_if(str.rbegin(), str.rend(),
                               [](unsigned char c)
                               { return !std::isspace(c); });
        str.erase(it.base(), str.end());
        return str;
    }

    std::string trim(std::string str)
    {
        return ltrim(rtrim(str));
    }

    std::string upper(std::string str)
    {
        for (char &ch : str)
        {
            if (ch >= 'a' && ch <= 'z')
                ch += 'A' - 'a';
        }
        return str;
    }

    std::string lower(std::string str)
    {
        for (char &ch : str)
        {
            if (ch >= 'A' && ch <= 'Z')
                ch -= 'A' - 'a';
        }
        return str;
    }

    std::string title(std::string str)
    {
        if (str[0] >= 'a' && str[0] <= 'z')
            str[0] += 'A' - 'a';
        for (std::size_t i = 1; i < str.size(); ++i)
        {
            if (std::isspace(str[i - 1]) && str[i] >= 'a' && str[i] <= 'z')
                str[i] += 'A' - 'a';
            else if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] -= 'A' - 'a';
        }
        return str;
    }

    inline TimerResult now()
    {
        int64_t tmp = std::chrono::high_resolution_clock::now()
                          .time_since_epoch()
                          .count();
        return TimerResult{(double)tmp, (double)tmp / 1e3,
                           (double)tmp / 1e6, (double)tmp / 1e9};
    }

    template <class F, class... Args>
    TimerResult timer(F f, const Args &...args)
    {
        TimerResult start = now();
        f(args...);
        return now() - start;
    }

    void sleep(double s)
    {
        std::this_thread::sleep_for(
            std::chrono::duration<double>(s));
    }

    int randomint(int min, int max)
    {
        static std::mt19937 gen(now());
        return std::uniform_int_distribution<>(min, max)(gen);
    }

    double uniform(double min, double max)
    {
        static std::mt19937 gen(now());
        return std::uniform_real_distribution<>(min, max)(gen);
    }

    template <class T>
    auto choice(const T &container) -> decltype(*std::begin(container))
    {
        if (container.empty())
            throw std::invalid_argument("...");
        auto it = std::begin(container);
        std::advance(it, randomint(0, container.size() - 1));
        return *it;
    }

    struct PartitionResult
    {
        std::string left;
        std::string middle;
        std::string right;
        friend std::ostream &operator<<(
            std::ostream &os, const PartitionResult &pr)
        {
            return os << '(' << pr.left << ", " << pr.middle
                      << ", " << pr.right << ')';
        }
    };

    PartitionResult partition(
        const std::string &text, const std::string &sep)
    {
        size_t pos = text.find(sep);
        if (pos == std::string::npos)
            return PartitionResult{text, "", ""};
        return PartitionResult{
            text.substr(0, pos),
            text.substr(pos, sep.size()),
            text.substr(pos + sep.size())};
    }

    std::vector<std::string> split(
        std::string text, const std::string &sep = " ")
    {
        std::vector<std::string> vec;
        PartitionResult pr;
        while ((pr = partition(text, sep)).right != "")
        {
            vec.push_back(pr.left);
            text = pr.right;
        }
        vec.push_back(pr.left);
        return vec;
    }

    std::string join(
        const std::vector<std::string> &vec, const std::string &sep = "")
    {
        if (vec.empty())
            return "";
        std::stringstream ss;
        auto it = vec.begin();
        ss << *it;
        while (++it != vec.end())
        {
            ss << sep << *it;
        }
        return ss.str();
    }
}