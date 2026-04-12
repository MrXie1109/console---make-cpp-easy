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
#include <stdexcept>
#include <string>

namespace console
{
    class console_error : public std::runtime_error
    {
    public:
        console_error(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    class fatal_logging : public console_error
    {
    public:
        fatal_logging(const std::string &msg)
            : console_error(msg) {}
    };

    class bad_format : public console_error
    {
    public:
        bad_format(const std::string &msg)
            : console_error(msg) {}
    };

    class file_error : public console_error
    {
    public:
        file_error(const std::string &msg)
            : console_error(msg) {}
    };

    class bad_get : public console_error
    {
    public:
        bad_get(const std::string &msg)
            : console_error(msg) {}
    };

    class multiarray_error : public console_error
    {
    public:
        multiarray_error(const std::string &msg)
            : console_error(msg) {}
    };

    class container_error : public console_error
    {
    public:
        container_error(const std::string &msg)
            : console_error(msg) {}
    };

    class index_error : public console_error
    {
    public:
        index_error(const std::string &msg)
            : console_error(msg) {}
    };

    class bad_maybe_access : public console_error
    {
    public:
        bad_maybe_access(const std::string &msg)
            : console_error(msg) {}
    };
}
