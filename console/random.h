/**
 * @file random.h
 * @brief 提供随机数生成、随机选择、随机打乱等实用工具。
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
#include <random>
#include <chrono>
#include <cstdint>
#include <utility>
#include <initializer_list>
#include "csexc.h"

namespace console
{
    /**
     * @brief 获取一个全局的、以当前时间戳为种子的 Mersenne Twister 随机数引擎。
     * @details 该函数返回一个静态的 std::mt19937 对象的引用，引擎使用高精度时钟的当前时间点进行初始化。
     * @return std::mt19937& 随机数引擎的引用。
     */
    inline std::mt19937 &default_gen()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now()
                                    .time_since_epoch()
                                    .count());
        return gen;
    }

    /**
     * @brief 生成一个指定范围内的随机整数（均匀分布）。
     * @tparam T 整数类型，默认为 int。
     * @param min 最小值（包含），默认为 0。
     * @param max 最大值（包含），默认为 32767。
     * @param gen 使用的随机数引擎，默认为 default_gen()。
     * @return T 在 [min, max] 区间内的随机整数。
     */
    template <class T = int>
    T randint(T min = 0, T max = 32767,
              std::mt19937 &gen = default_gen())
    {
        return std::uniform_int_distribution<T>(min, max)(gen);
    }

    /**
     * @brief 生成一个指定范围内的随机浮点数（均匀分布）。
     * @tparam T 浮点数类型，默认为 double。
     * @param min 最小值（包含），默认为 0.0。
     * @param max 最大值（包含），默认为 1.0。
     * @param gen 使用的随机数引擎，默认为 default_gen()。
     * @return T 在 [min, max] 区间内的随机浮点数。
     */
    template <class T = double>
    T uniform(T min = 0.0, T max = 1.0,
              std::mt19937 &gen = default_gen())
    {
        return std::uniform_real_distribution<T>(min, max)(gen);
    }

    /**
     * @brief 从容器中随机选择一个元素。
     * @tparam C 容器类型，必须支持 std::begin 和 std::end 迭代器以及 size() 方法。
     * @param c 要从中选择的容器（支持左值或右值引用）。
     * @param gen 使用的随机数引擎，默认为 default_gen()。
     * @return decltype(*std::begin(c)) 所选元素的引用。
     * @throw container_error 如果容器为空。
     */
    template <class C>
    auto choice(C &&c, std::mt19937 &gen = default_gen())
        -> decltype(*std::begin(c))
    {
        if (std::begin(c) == std::end(c))
            throw container_error("Empty container");
        return *std::next(std::begin(c),
                          randint<size_t>(0, c.size() - 1, gen));
    }

    /**
     * @brief 从 std::initializer_list 中随机选择一个元素（重载版本）。
     * @tparam T 元素类型。
     * @param init 初始化列表。
     * @param gen 使用的随机数引擎，默认为 default_gen()。
     * @return decltype(*std::begin(init)) 所选元素的引用。
     * @throw container_error 如果初始化列表为空。
     */
    template <class T>
    auto choice(std::initializer_list<T> init,
                std::mt19937 &gen = default_gen())
        -> decltype(*std::begin(init))
    {
        return choice<std::initializer_list<T>>((init), gen);
    }

    /**
     * @brief 随机打乱容器中元素的顺序（Fisher-Yates 洗牌算法）。
     * @tparam C 容器类型，必须支持 std::begin 和 std::end 迭代器、size() 以及 swap 操作。
     * @param c 要打乱的容器（支持左值或右值引用）。
     * @param gen 使用的随机数引擎，默认为 default_gen()。
     * @throw container_error 如果容器为空。
     */
    template <class C>
    void shuffle(C &&c, std::mt19937 &gen = default_gen())
    {
        if (std::begin(c) == std::end(c))
            throw container_error("Empty container");
        for (size_t i = c.size() - 1; i > 0; i--)
        {
            auto j = randint<size_t>(0, i, gen);
            std::swap(*std::next(std::begin(c), i),
                      *std::next(std::begin(c), j));
        }
    }
}
