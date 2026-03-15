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

    class jdt_range_error : public console_error
    {
    public:
        jdt_range_error(const std::string &msg)
            : console_error(msg) {}
    };

    class bad_format : public console_error
    {
    public:
        bad_format(const std::string &msg)
            : console_error(msg) {}
    };

    class file_not_found_error : public console_error
    {
    public:
        file_not_found_error(const std::string &msg)
            : console_error(msg) {}
    };

    class bad_get : public console_error
    {
    public:
        bad_get(const std::string &msg)
            : console_error(msg) {}
    };

    class ndarray_error : public console_error
    {
    public:
        ndarray_error(const std::string &msg)
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
}
