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
#include <typeinfo>
#include <memory>
#include <string>
#include "sfinae.h"
#ifdef __GNUG__
#include <cxxabi.h>
#endif

namespace console
{
    std::string tiname(const std::type_info &ti)
    {
#ifdef _MSC_VER
        return ti.name();
#elif defined(__GNUG__)
        int status = 0;
        std::unique_ptr<char, void (*)(void *)> result(
            abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status),
            std::free);
        return (status == 0) ? result.get() : ti.name();
#else
        return ti.name();
#endif
    }

    template <class T>
    enable_if_string<typename std::decay<T>::type>
    repr(T &&value, std::ostream &os = std::cout)
    {
        os << '"' << value << '"';
    }

    template <class T>
    enable_if_char<typename std::decay<T>::type>
    repr(T &&value, std::ostream &os = std::cout)
    {
        os << "'" << value << "'";
    }

    template <class T>
    typename std::enable_if<
        std::is_same<typename std::decay<T>::type, bool>::value>::type
    repr(T &&value, std::ostream &os = std::cout)
    {
        os << (value ? "true" : "false");
    }

    template <class T>
    typename std::enable_if<
        std::is_same<typename std::decay<T>::type, std::nullptr_t>::value>::type
    repr(T &&value, std::ostream &os = std::cout)
    {
        os << "nullptr";
    }

    template <class Ret, class... Args>
    void repr(Ret (*f)(Args...), std::ostream &os = std::cout)
    {
        if (f)
            os << "<function at " << (void *)f << '>';
        else
            os << "nullptr";
    }

    template <class T>
    typename std::enable_if<
        !std::is_same<typename std::decay<T>::type, bool>::value &&
        !is_string<typename std::decay<T>::type>::value &&
        !is_char<typename std::decay<T>::type>::value &&
        !std::is_function<
            typename std::remove_pointer<
                typename std::decay<T>::type>::type>::value &&
        is_printable<typename std::decay<T>::type>::value>::type
    repr(T &&value, std::ostream &os = std::cout)
    {
        os << value;
    }

    template <class T>
    typename std::enable_if<
        !std::is_same<typename std::decay<T>::type, std::nullptr_t>::value &&
        !is_string<typename std::decay<T>::type>::value &&
        !is_char<typename std::decay<T>::type>::value &&
        !is_printable<typename std::decay<T>::type>::value>::type
    repr(T &&value, std::ostream &os = std::cout)
    {
        os << "<class \""
           << tiname(typeid(typename std::decay<T>::type))
           << "\">";
    }
}
