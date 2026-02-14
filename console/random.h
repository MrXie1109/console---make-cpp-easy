#pragma once
#include <random>
#include <chrono>
#include <cstdint>
#include <utility>

namespace console
{
    using namespace std;

    inline mt19937 &GEN()
    {
        static mt19937 gen(chrono::high_resolution_clock::now()
                               .time_since_epoch()
                               .count());
        return gen;
    }

    template <class T = int>
    T randint(T min = 0, T max = 32767,
              mt19937 &gen = GEN())
    {
        return uniform_int_distribution<T>(min, max)(gen);
    }

    template <class T = double>
    T uniform(T min = 0.0, T max = 1.0,
              mt19937 &gen = GEN())
    {
        return uniform_real_distribution<T>(min, max)(gen);
    }

    template <class T>
    auto choice(T &&t, mt19937 &gen = GEN()) -> decltype(*begin(t))
    {
        if (t.empty())
            throw invalid_argument("Empty container");
        auto it = begin(t);
        size_t index = randint(0, t.size() - 1, gen);
        for (size_t i = 0; i < index; i++)
            ++it;
        return *it;
    }

    template <class T>
    void shuffle(T &&t, mt19937 &gen = GEN())
    {
        auto get = [&](size_t index) -> decltype(*begin(t))
        {
            auto it = begin(t);
            for (size_t i = 0; i < index; i++)
                ++it;
            return *it;
        };
        for (size_t i = t.size() - 1; i > 0; i--)
        {
            auto j = randint<size_t>(0, i);
            swap(get(i), get(j));
        }
    }
}