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
    inline std::mt19937 &default_gen()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now()
                                    .time_since_epoch()
                                    .count());
        return gen;
    }

    template <class T = int>
    T randint(T min = 0, T max = 32767,
              std::mt19937 &gen = default_gen())
    {
        return std::uniform_int_distribution<T>(min, max)(gen);
    }

    template <class T = double>
    T uniform(T min = 0.0, T max = 1.0,
              std::mt19937 &gen = default_gen())
    {
        return std::uniform_real_distribution<T>(min, max)(gen);
    }

    template <class C>
    auto choice(C &&c, std::mt19937 &gen = default_gen())
        -> decltype(*std::begin(c))
    {
        if (std::begin(c) == std::end(c))
            throw container_error("Empty container");
        return *std::next(std::begin(c),
                          randint<size_t>(0, c.size() - 1, gen));
    }

    template <class T>
    auto choice(std::initializer_list<T> init,
                std::mt19937 &gen = default_gen())
        -> decltype(*std::begin(init))
    {
        return choice<std::initializer_list<T>>((init), gen);
    }

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
