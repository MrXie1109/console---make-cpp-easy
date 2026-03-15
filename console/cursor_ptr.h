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
#include <cstddef>

namespace console
{
    /**
     * @brief 双指针游标智能指针：分离所有权与访问位置
     *
     * @details
     * 本类通过维护两个指针（原始指针和游标指针）实现内存自动管理与指针运算的共存：
     * - original_ptr: 持有内存所有权，负责资源释放
     * - current_ptr: 表示当前访问位置，支持指针算术运算
     *
     * @tparam T 元素类型，支持对象类型(T)和数组类型(T[])
     *
     * @note 所有权规则：
     * - 只有通过原始指针构造或移动构造的实例拥有内存所有权
     * - 复制构造/赋值的实例仅持有游标位置，不拥有所有权
     * - 移动操作会转移所有权，但源对象的游标位置保持不变
     *
     * @warning 使用约束：
     * 1. 复制赋值(cp1 = cp2)要求cp2的生命周期覆盖cp1的使用周期
     * 2. 指针算术运算不进行边界检查，行为与原始指针一致
     * 3. 需要确保new/delete与new[]/delete[]的正确匹配
     * 4. 游标移动可能导致野指针，需自行保证内存有效性
     *
     * @par 适用场景：
     * - 需要自动内存管理同时支持指针运算
     * - 需要多个游标并发访问同一内存区域
     * - 与C风格API交互时需要传递指针范围
     *
     * @see std::unique_ptr, std::span
     */

    template <class T>
    class cursor_ptr
    {
        T *original_ptr;
        T *curent_ptr;

    public:
        cursor_ptr() : original_ptr(nullptr), curent_ptr(nullptr) {}
        cursor_ptr(T *p) : original_ptr(p), curent_ptr(p) {}
        cursor_ptr(const cursor_ptr &cp)
            : original_ptr(nullptr), curent_ptr(cp.curent_ptr) {}
        cursor_ptr(cursor_ptr &&cp)
            : original_ptr(cp.original_ptr), curent_ptr(cp.curent_ptr)
        {
            cp.original_ptr = nullptr;
        }
        T &operator*() { return *curent_ptr; }
        T *operator->() { return curent_ptr; }
        T &operator[](size_t i) { return *(curent_ptr + i); }
        T *get() { return curent_ptr; }
        operator T *() { return curent_ptr; }
        const T &operator*() const { return *curent_ptr; }
        const T *operator->() const { return curent_ptr; }
        const T &operator[](size_t i) const { return *(curent_ptr + i); }
        const T *get() const { return curent_ptr; }
        operator const T *() const { return curent_ptr; }
        ~cursor_ptr() { delete original_ptr; }
        cursor_ptr &operator++()
        {
            ++curent_ptr;
            return *this;
        }
        cursor_ptr operator++(int)
        {
            cursor_ptr tmp(*this);
            ++curent_ptr;
            return tmp;
        }
        cursor_ptr &operator--()
        {
            --curent_ptr;
            return *this;
        }
        cursor_ptr operator--(int)
        {
            cursor_ptr tmp(*this);
            --curent_ptr;
            return tmp;
        }
        cursor_ptr operator+(int sep) const
        {
            cursor_ptr cp;
            cp.curent_ptr = curent_ptr + sep;
            return cp;
        }
        cursor_ptr operator-(int sep) const
        {
            cursor_ptr cp;
            cp.curent_ptr = curent_ptr - sep;
            return cp;
        }
        const cursor_ptr &operator+=(int sep)
        {
            curent_ptr += sep;
            return *this;
        }
        const cursor_ptr &operator-=(int sep)
        {
            curent_ptr -= sep;
            return *this;
        }
        int operator-(const cursor_ptr &cp) const
        {
            return curent_ptr - cp.curent_ptr;
        }
        bool operator==(const cursor_ptr &cp) const
        {
            return curent_ptr == cp.curent_ptr;
        }
        bool operator==(const T *p) const
        {
            return curent_ptr == p;
        }
        friend bool operator==(const T *p, const cursor_ptr &cp)
        {
            return cp == p;
        }
        bool operator!=(const cursor_ptr &cp) const
        {
            return curent_ptr != cp.curent_ptr;
        }
        bool operator!=(const T *p) const
        {
            return curent_ptr != p;
        }
        friend bool operator!=(const T *p, const cursor_ptr &cp)
        {
            return cp != p;
        }
        const cursor_ptr &operator=(T *p)
        {
            if (original_ptr == p)
                return *this;
            delete original_ptr;
            original_ptr = p;
            curent_ptr = p;
            return *this;
        }
        const cursor_ptr &operator=(const cursor_ptr &cp)
        {
            if (this == &cp)
                return *this;
            delete original_ptr;
            curent_ptr = cp.curent_ptr;
            return *this;
        }
        const cursor_ptr &operator=(cursor_ptr &&cp)
        {
            if (this == &cp)
                return *this;
            delete original_ptr;
            curent_ptr = cp.curent_ptr;
            original_ptr = cp.original_ptr;
            cp.original_ptr = nullptr;
            return *this;
        }
        void swap(cursor_ptr &cp)
        {
            T *p1 = curent_ptr, *p2 = original_ptr;
            curent_ptr = cp.curent_ptr;
            original_ptr = cp.original_ptr;
            cp.curent_ptr = p1;
            cp.original_ptr = p2;
        }
    };

    template <class T>
    class cursor_ptr<T[]>
    {
        T *original_ptr;
        T *curent_ptr;

    public:
        cursor_ptr() : original_ptr(nullptr), curent_ptr(nullptr) {}
        cursor_ptr(T *p) : original_ptr(p), curent_ptr(p) {}
        cursor_ptr(const cursor_ptr &cp)
            : original_ptr(nullptr), curent_ptr(cp.curent_ptr) {}
        cursor_ptr(cursor_ptr &&cp)
            : original_ptr(cp.original_ptr), curent_ptr(cp.curent_ptr)
        {
            cp.original_ptr = nullptr;
        }
        T &operator*() { return *curent_ptr; }
        T *operator->() { return curent_ptr; }
        T &operator[](size_t i) { return *(curent_ptr + i); }
        T *get() { return curent_ptr; }
        operator T *() { return curent_ptr; }
        const T &operator*() const { return *curent_ptr; }
        const T *operator->() const { return curent_ptr; }
        const T &operator[](size_t i) const { return *(curent_ptr + i); }
        const T *get() const { return curent_ptr; }
        operator const T *() const { return curent_ptr; }
        ~cursor_ptr() { delete[] original_ptr; }
        cursor_ptr &operator++()
        {
            ++curent_ptr;
            return *this;
        }
        cursor_ptr operator++(int)
        {
            cursor_ptr tmp(*this);
            ++curent_ptr;
            return tmp;
        }
        cursor_ptr &operator--()
        {
            --curent_ptr;
            return *this;
        }
        cursor_ptr operator--(int)
        {
            cursor_ptr tmp(*this);
            --curent_ptr;
            return tmp;
        }
        cursor_ptr operator+(int sep) const
        {
            cursor_ptr cp;
            cp.curent_ptr = curent_ptr + sep;
            return cp;
        }
        cursor_ptr operator-(int sep) const
        {
            cursor_ptr cp;
            cp.curent_ptr = curent_ptr - sep;
            return cp;
        }
        const cursor_ptr &operator+=(int sep)
        {
            curent_ptr += sep;
            return *this;
        }
        const cursor_ptr &operator-=(int sep)
        {
            curent_ptr -= sep;
            return *this;
        }
        int operator-(const cursor_ptr &cp) const
        {
            return curent_ptr - cp.curent_ptr;
        }
        bool operator==(const cursor_ptr &cp) const
        {
            return curent_ptr == cp.curent_ptr;
        }
        bool operator==(const T *p) const
        {
            return curent_ptr == p;
        }
        friend bool operator==(const T *p, const cursor_ptr &cp)
        {
            return cp == p;
        }
        bool operator!=(const cursor_ptr &cp) const
        {
            return curent_ptr != cp.curent_ptr;
        }
        bool operator!=(const T *p) const
        {
            return curent_ptr != p;
        }
        friend bool operator!=(const T *p, const cursor_ptr &cp)
        {
            return cp != p;
        }
        const cursor_ptr &operator=(T *p)
        {
            if (original_ptr == p)
                return *this;
            delete[] original_ptr;
            original_ptr = p;
            curent_ptr = p;
            return *this;
        }
        const cursor_ptr &operator=(const cursor_ptr &cp)
        {
            if (this == &cp)
                return *this;
            delete[] original_ptr;
            curent_ptr = cp.curent_ptr;
            return *this;
        }
        const cursor_ptr &operator=(cursor_ptr &&cp)
        {
            if (this == &cp)
                return *this;
            delete[] original_ptr;
            curent_ptr = cp.curent_ptr;
            original_ptr = cp.original_ptr;
            cp.original_ptr = nullptr;
            return *this;
        }
        void swap(cursor_ptr &cp)
        {
            T *p1 = curent_ptr, *p2 = original_ptr;
            curent_ptr = cp.curent_ptr;
            original_ptr = cp.original_ptr;
            cp.curent_ptr = p1;
            cp.original_ptr = p2;
        }
    };
}
