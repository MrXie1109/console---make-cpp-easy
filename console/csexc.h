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
}