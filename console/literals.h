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
#include "strpp.h"
#include "time.h"

namespace console
{
    namespace literals
    {
#if __cplusplus < 201703L
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
#else
        using namespace std::literals::string_literals;
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
