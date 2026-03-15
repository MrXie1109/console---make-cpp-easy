#pragma once
#include <type_traits>
#include <iterator>

namespace console
{
    template <typename T, typename = void>
    struct is_container : std::false_type
    {
    };

    template <typename T>
    struct is_container<T, typename std::enable_if<
                               sizeof(decltype(std::declval<T>().begin())) &&
                               sizeof(decltype(std::declval<T>().end())) &&
                               std::is_integral<decltype(std::declval<T>().size())>::value>::type> : std::true_type
    {
    };

    template <typename F, typename Ret, typename = void>
    struct is_callable : std::false_type
    {
    };

    template <typename F, typename Ret>
    struct is_callable<F, Ret, typename std::enable_if<std::is_convertible<decltype(std::declval<F>()()), Ret>::value>::type> : std::true_type
    {
    };

    template <typename T, typename = void>
    struct is_iterator : std::false_type
    {
    };

    template <typename T>
    struct is_iterator<T, typename std::enable_if<
                              sizeof(typename std::iterator_traits<T>::iterator_category)>::type> : std::true_type
    {
    };

    template <typename T, typename Idx, typename = void>
    struct has_subscript : std::false_type
    {
    };

    template <typename T, typename Idx>
    struct has_subscript<T, Idx, typename std::enable_if<sizeof(decltype(std::declval<T>()[std::declval<Idx>()]))>::type> : std::true_type
    {
    };

    // 基础模板：默认不是字符串
    template <typename T, typename = void>
    struct is_string : std::false_type
    {
    };

    // ----- 1. 全特化：C风格字符串 -----
    template <>
    struct is_string<const char *> : std::true_type
    {
    };

    template <>
    struct is_string<char *> : std::true_type
    {
    };

    // ----- 2. 偏特化：字符数组 -----
    template <size_t N>
    struct is_string<char[N]> : std::true_type
    {
    };

    template <size_t N>
    struct is_string<const char[N]> : std::true_type
    {
    };

    // ----- 3. 偏特化：宽字符版本 -----
    template <>
    struct is_string<const wchar_t *> : std::true_type
    {
    };

    template <>
    struct is_string<wchar_t *> : std::true_type
    {
    };

    template <size_t N>
    struct is_string<wchar_t[N]> : std::true_type
    {
    };

    // ----- 4. 偏特化：现代C++字符串类型（通过SFINAE）-----
    template <typename T>
    struct is_string<T, std::void_t<
                            typename T::value_type,               // 必须有value_type
                            decltype(std::declval<T>().c_str()),  // 必须有c_str()
                            decltype(std::declval<T>().length()), // 必须有length()
                            std::enable_if_t<std::is_same_v<
                                typename T::value_type, char>> // value_type必须是char
                            >> : std::true_type
    {
    };

    template <typename CharT, typename Traits, typename Alloc>
    struct is_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type
    {
    };

#if __cplusplus >= 201703L
    template <typename CharT, typename Traits>
    struct is_string<std::basic_string_view<CharT, Traits>> : std::true_type
    {
    };
#endif

    template <typename T>
    using enable_if_container = typename std::enable_if<is_container<T>::value>::type;

    template <typename F, typename Ret>
    using enable_if_callable = typename std::enable_if<is_callable<F, Ret>::value>::type;

    template <typename T>
    using enable_if_iterator = typename std::enable_if<is_iterator<T>::value>::type;

    template <typename T>
    using enable_if_string = typename std::enable_if<is_string<T>::value>::type;
}
