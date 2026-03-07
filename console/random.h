#pragma once
#include <random>
#include <chrono>
#include <cstdint>
#include <utility>
#include <initializer_list>
#include "csexc.h"

namespace console
{
    inline std::mt19937 &GEN()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now()
                                    .time_since_epoch()
                                    .count());
        return gen;
    }

    template <class T = int>
    T randint(T min = 0, T max = 32767,
              std::mt19937 &gen = GEN())
    {
        return std::uniform_int_distribution<T>(min, max)(gen);
    }

    template <class T = double>
    T uniform(T min = 0.0, T max = 1.0,
              std::mt19937 &gen = GEN())
    {
        return std::uniform_real_distribution<T>(min, max)(gen);
    }

    template <class T>
    auto choice(T &&t, std::mt19937 &gen = GEN()) -> decltype(*std::begin(t))
    {
        if (std::begin(t) == std::end(t))
            throw container_error("Empty container");
        auto it = std::begin(t);
        size_t index = randint<size_t>(0, t.size() - 1, gen);
        for (size_t i = 0; i < index; i++)
            ++it;
        return *it;
    }

    template <class T>
    auto choice(std::initializer_list<T> init, std::mt19937 &gen = GEN())
        -> decltype(*std::begin(init))
    {
        return choice<std::initializer_list<T>>(
            std::forward<std::initializer_list<T>>(init),
            gen);
    }

    template <class T>
    void shuffle(T &&t, std::mt19937 &gen = GEN())
    {
        auto get = [&](size_t index) -> decltype(*std::begin(t))
        {
            auto it = std::begin(t);
            for (size_t i = 0; i < index; i++)
                ++it;
            return *it;
        };
        for (size_t i = t.size() - 1; i > 0; i--)
        {
            auto j = randint<size_t>(0, i);
            std::swap(get(i), get(j));
        }
    }
}
