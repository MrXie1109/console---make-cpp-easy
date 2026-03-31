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
#include <type_traits>
#include <iterator>
#include "outfwd.h"

namespace console
{
    template <class T, class = void>
    struct is_container : std::false_type
    {
    };

    template <class T>
    struct is_container<
        T, typename std::enable_if<
               sizeof(decltype(std::begin(std::declval<T>()))) &&
               sizeof(decltype(std::end(std::declval<T>())))>::type>
        : std::true_type
    {
    };

    template <class F, class = void, class... Args>
    struct is_callable : std::false_type
    {
    };

    template <class F, class... Args>
    struct is_callable<F,
                       typename std::enable_if<
                           std::is_convertible<
                               decltype(std::declval<F>()(std::declval<Args>()...)),
                               void>::value>::type,
                       Args...>
        : std::true_type
    {
    };

    template <class T, class = void>
    struct is_iterator : std::false_type
    {
    };

    template <class T>
    struct is_iterator<T, typename std::enable_if<
                              sizeof(
                                  typename std::iterator_traits<T>::
                                      iterator_category)>::type>
        : std::true_type
    {
    };

    template <class T, class Idx, class = void>
    struct has_subscript : std::false_type
    {
    };

    template <class T, class Idx>
    struct has_subscript<T, Idx,
                         typename std::enable_if<
                             sizeof(decltype(std::declval<T>()
                                                 [std::declval<Idx>()]))>::type>
        : std::true_type
    {
    };

    template <class T, class = void>
    struct is_string : std::false_type
    {
    };

    template <>
    struct is_string<char *> : std::true_type
    {
    };

    template <>
    struct is_string<wchar_t *> : std::true_type
    {
    };

    template <>
    struct is_string<char16_t *> : std::true_type
    {
    };

    template <>
    struct is_string<char32_t *> : std::true_type
    {
    };

    template <class CharT, class Traits, class Alloc>
    struct is_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type
    {
    };

#if __cplusplus >= 201703L
    template <class CharT, class Traits>
    struct is_string<std::basic_string_view<CharT, Traits>> : std::true_type
    {
    };
#endif

    template <class T, class = void>
    struct is_printable : std::false_type
    {
    };

    template <class T>
    struct is_printable<T, typename std::enable_if<
                               sizeof(
                                   decltype(std::declval<std::ostream &>()
                                            << std::declval<T>()))>::type>
        : std::true_type
    {
    };

    template <class T, class = void>
    struct is_char : std::false_type
    {
    };

    template <>
    struct is_char<char> : std::true_type
    {
    };

    template <>
    struct is_char<signed char> : std::true_type
    {
    };

    template <>
    struct is_char<unsigned char> : std::true_type
    {
    };

    template <>
    struct is_char<wchar_t> : std::true_type
    {
    };

    template <>
    struct is_char<char16_t> : std::true_type
    {
    };

    template <>
    struct is_char<char32_t> : std::true_type
    {
    };

    template <class T>
    using enable_if_container =
        typename std::enable_if<is_container<T>::value>::type;

    template <class T>
    using enable_if_not_container =
        typename std::enable_if<!is_container<T>::value>::type;

    template <class F, class... Args>
    using enable_if_callable =
        typename std::enable_if<is_callable<F, Args...>::value>::type;

    template <class F, class... Args>
    using enable_if_not_callable =
        typename std::enable_if<!is_callable<F, Args...>::value>::type;

    template <class T>
    using enable_if_iterator =
        typename std::enable_if<is_iterator<T>::value>::type;

    template <class T>
    using enable_if_not_iterator =
        typename std::enable_if<!is_iterator<T>::value>::type;

    template <class T>
    using enable_if_string =
        typename std::enable_if<is_string<
            typename std::decay<T>::type>::value>::type;

    template <class T>
    using enable_if_not_string =
        typename std::enable_if<!is_string<
            typename std::decay<T>::type>::value>::type;

    template <class T>
    using enable_if_printable =
        typename std::enable_if<is_printable<T>::value>::type;

    template <class T>
    using enable_if_not_printable =
        typename std::enable_if<!is_printable<T>::value>::type;

    template <class T>
    using enable_if_char = typename std::enable_if<is_char<
        typename std::decay<T>::type>::value>::type;

    template <class T>
    using enable_if_not_char = typename std::enable_if<!is_char<
        typename std::decay<T>::type>::value>::type;
}
