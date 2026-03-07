#pragma once
#include <stdexcept>
#include <string>

namespace console
{
    class fatal_logging : public std::runtime_error
    {
    public:
        fatal_logging(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    class jdt_range_error : public std::invalid_argument
    {
    public:
        jdt_range_error(const std::string &msg)
            : std::invalid_argument(msg) {}
    };

    class bad_format : public std::invalid_argument
    {
    public:
        bad_format(const std::string &msg)
            : std::invalid_argument(msg) {}
    };

    class file_not_found_error : public std::runtime_error
    {
    public:
        file_not_found_error(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    class bad_get : public std::invalid_argument
    {
    public:
        bad_get(const std::string &msg)
            : std::invalid_argument(msg) {}
    };

    class ndarray_error : public std::runtime_error
    {
    public:
        ndarray_error(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    class container_error : public std::invalid_argument
    {
    public:
        container_error(const std::string &msg)
            : std::invalid_argument(msg) {}
    };

    class index_error : public std::out_of_range
    {
    public:
        index_error(const std::string &msg)
            : std::out_of_range(msg) {}
    };
}
