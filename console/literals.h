#pragma once
#include "strpp.h"
#include "time.h"

namespace console
{
    namespace literals
    {
#if __cplusplus >= 201103L
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"
#endif
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4455)
#endif
        std::string operator""s(const char *str, size_t)
        {
            return std::string(str);
        }
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
#endif

        Time operator""_ns(unsigned long long ns) { return Time(ns); }
        Time operator""_us(unsigned long long us) { return Time(us * 1e3); }
        Time operator""_ms(unsigned long long ms) { return Time(ms * 1e6); }
        Time operator""_s(unsigned long long s) { return Time(s * 1e9); }
        Time operator""_ns(long double ns) { return Time(ns); }
        Time operator""_us(long double us) { return Time(us * 1e3); }
        Time operator""_ms(long double ms) { return Time(ms * 1e6); }
        Time operator""_s(long double s) { return Time(s * 1e9); }

        f_string operator""_f(const char *str, size_t) { return str; }
    }
}