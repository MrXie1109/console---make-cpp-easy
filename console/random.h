#pragma once
#include <random>
#include <chrono>
#include <cstdint>

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

    int64_t randint(int64_t min = 0, int64_t max = 32767,
                    mt19937 &gen = GEN())
    {
        return uniform_int_distribution<int64_t>(min, max)(gen);
    }

    long double uniform(double min = 0.0, double max = 1.0,
                        mt19937 &gen = GEN())
    {
        return uniform_real_distribution<long double>(min, max)(gen);
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
}