/**
 * @file csexc.h
 * @brief 定义 console 库使用的自定义异常类层次结构。
 * @details 所有异常都继承自 console::console_error，后者派生自 std::runtime_error。
 * @author MrXie1109
 * @date 2026
 * @copyright MIT License
 */

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
    /**
     * @class console_error
     * @brief console 库所有异常的基类。
     * @details 派生自 std::runtime_error，用于捕获所有由 console 库抛出的异常。
     */
    class console_error : public std::runtime_error
    {
    public:
        /**
         * @brief 构造 console_error。
         * @param msg 错误描述信息。
         */
        console_error(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    /**
     * @class fatal_logging
     * @brief 表示致命日志错误，通常会导致程序终止。
     */
    class fatal_logging : public console_error
    {
    public:
        /**
         * @brief 构造 fatal_logging。
         * @param msg 错误描述信息。
         */
        fatal_logging(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class bad_format
     * @brief 表示格式化字符串错误，例如占位符与参数不匹配。
     */
    class bad_format : public console_error
    {
    public:
        /**
         * @brief 构造 bad_format。
         * @param msg 错误描述信息。
         */
        bad_format(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class file_error
     * @brief 表示文件操作错误，如打开失败、读取失败等。
     */
    class file_error : public console_error
    {
    public:
        /**
         * @brief 构造 file_error。
         * @param msg 错误描述信息。
         */
        file_error(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class bad_get
     * @brief 表示从 Item 或 Box 中获取类型不匹配或空值时发生的错误。
     * @see Item, Box
     */
    class bad_get : public console_error
    {
    public:
        /**
         * @brief 构造 bad_get。
         * @param msg 错误描述信息。
         */
        bad_get(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class multiarray_error
     * @brief 表示 MultiArray 多维数组操作中的错误，如维度不匹配。
     */
    class multiarray_error : public console_error
    {
    public:
        /**
         * @brief 构造 multiarray_error。
         * @param msg 错误描述信息。
         */
        multiarray_error(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class container_error
     * @brief 表示通用容器操作错误。
     */
    class container_error : public console_error
    {
    public:
        /**
         * @brief 构造 container_error。
         * @param msg 错误描述信息。
         */
        container_error(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class index_error
     * @brief 表示索引越界错误。
     */
    class index_error : public console_error
    {
    public:
        /**
         * @brief 构造 index_error。
         * @param msg 错误描述信息。
         */
        index_error(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class bad_maybe_access
     * @brief 表示对空的 Maybe 对象进行取值操作时抛出的异常。
     * @see Maybe
     */
    class bad_maybe_access : public console_error
    {
    public:
        /**
         * @brief 构造 bad_maybe_access。
         * @param msg 错误描述信息。
         */
        bad_maybe_access(const std::string &msg)
            : console_error(msg) {}
    };

    /**
     * @class domain_error
     * @brief 表示试图对无效的数学值域进行操作时抛出的异常。
     * @see std::domain_error
     */
    class domain_error : public console_error
    {
    public:
        /**
         * @brief 构造 domain_error。
         * @param msg 错误描述信息。
         */
        domain_error(const std::string &msg)
            : console_error(msg) {}
    };
}
