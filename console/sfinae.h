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

    template <typename T>
    using enable_if_container = typename std::enable_if<is_container<T>::value>::type;

    template <typename F, typename Ret>
    using enable_if_callable = typename std::enable_if<is_callable<F, Ret>::value>::type;

    template <typename T>
    using enable_if_iterator = typename std::enable_if<is_iterator<T>::value>::type;

}