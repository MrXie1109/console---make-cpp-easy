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
        return choice<std::initializer_list<T>>(
            std::forward<std::initializer_list<T>>(init),
            gen);
    }

    template <class C>
    void shuffle(C &&c, std::mt19937 &gen = default_gen())
    {
        for (size_t i = c.size() - 1; i > 0; i--)
        {
            auto j = randint<size_t>(0, i, gen);
            std::swap(*std::next(std::begin(c), i),
                      *std::next(std::begin(c), j));
        }
    }
}
