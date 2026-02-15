#pragma once
#include <stdexcept>
#include <string>

namespace console
{
    using namespace std;

    class fatal_logging : public runtime_error
    {
    public:
        fatal_logging(const string &msg)
            : runtime_error(msg) {}
    };

    class jdt_range_error : public invalid_argument
    {
    public:
        jdt_range_error(const string &msg)
            : invalid_argument(msg) {}
    };

    class bad_format : public invalid_argument
    {
    public:
        bad_format(const string &msg)
            : invalid_argument(msg) {}
    };

    class file_not_found_error : public runtime_error
    {
    public:
        file_not_found_error(const string &msg)
            : runtime_error(msg) {}
    };

    class bad_get : public invalid_argument
    {
    public:
        bad_get(const string &msg)
            : invalid_argument(msg) {}
    };
}