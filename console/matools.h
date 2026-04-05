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
#define _USE_MATH_DEFINES
#include <iostream>
#include <numeric>
#include <cmath>
#include "multiarray.h"
#include "random.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace console
{
    template <class T, size_t... Dims>
    double mean(const MultiArray<T, Dims...> &arr)
    {
        return double(sum(arr)) / arr.size();
    }

    template <class T, size_t... Dims>
    double variance(const MultiArray<T, Dims...> &arr, bool sample = true)
    {
        double m = mean(arr);
        double sq_sum = 0;
        arr.for_each([&](const T &x)
                     {
            double d = double(x) - m;
            sq_sum += d * d; });
        return sq_sum / (arr.size() - (sample ? 1 : 0));
    }

    template <class T, size_t... Dims>
    double stddev(const MultiArray<T, Dims...> &arr, bool sample = true)
    {
        return std::sqrt(variance(arr, sample));
    }

    template <class T, size_t N>
    T dot(const MultiArray<T, N> &a, const MultiArray<T, N> &b)
    {
        return std::inner_product(a.fbegin(), a.fend(), b.fbegin(), T{});
    }

    template <class T, size_t N>
    double norm(const MultiArray<T, N> &a)
    {
        return std::sqrt(double(dot(a, a)));
    }

    template <class T, size_t N>
    double cosine(const MultiArray<T, N> &a, const MultiArray<T, N> &b)
    {
        return dot(a, b) / (norm(a) * norm(b));
    }

    template <class T, size_t N>
    MultiArray<T, N> normalize(const MultiArray<T, N> &a)
    {
        double len = norm(a);
        if (len == 0)
            return a;
        MultiArray<T, N> result;
        auto ai = a.fbegin();
        auto ri = result.fbegin();
        while (ri != result.fend())
            *ri++ = *ai++ / len;
        return result;
    }

    template <class T, size_t M, size_t N, size_t K>
    MultiArray<T, M, K> matmul(const MultiArray<T, M, N> &A,
                               const MultiArray<T, N, K> &B)
    {
        MultiArray<T, M, K> C{};
        for (size_t i = 0; i < M; i++)
            for (size_t k = 0; k < K; k++)
                for (size_t j = 0; j < N; j++)
                    C[i][k] += A[i][j] * B[j][k];
        return C;
    }

    template <class T, size_t M, size_t N>
    MultiArray<T, N, M> transpose(const MultiArray<T, M, N> &A)
    {
        MultiArray<T, N, M> B;
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                B[j][i] = A[i][j];
        return B;
    }

    template <class T, size_t N>
    MultiArray<T, N, N> identity()
    {
        MultiArray<T, N, N> I{};
        for (size_t i = 0; i < N; i++)
            I[i][i] = T{1};
        return I;
    }

    template <class T, size_t N>
    T trace(const MultiArray<T, N, N> &A)
    {
        T result{};
        for (size_t i = 0; i < N; i++)
            result += A[i][i];
        return result;
    }

    template <class T>
    MultiArray<T, 3> cross(const MultiArray<T, 3> &a, const MultiArray<T, 3> &b)
    {
        return MultiArray<T, 3>{
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> clamp(const MultiArray<T, Dims...> &arr,
                                 T low, T high)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
        {
            *ri = *ai < low ? low : (*ai > high ? high : *ai);
            ++ri;
            ++ai;
        }
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> abs(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::abs(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    void randomize(MultiArray<T, Dims...> &arr, T min = 0, T max = 100)
    {
        std::uniform_int_distribution<T> dis(min, max);
        arr.for_each([&](T &x)
                     { x = dis(default_gen()); });
    }

    template <class T, size_t... Dims>
    void randomize_normal(MultiArray<T, Dims...> &arr, T mean = 0, T stddev = 1)
    {
        std::normal_distribution<T> dis(mean, stddev);
        arr.for_each([&](T &x)
                     { x = dis(default_gen()); });
    }

    template <class T, size_t... Dims>
    void linspace(MultiArray<T, Dims...> &arr, T start, T end)
    {
        size_t n = arr.size();
        for (size_t i = 0; i < n; i++)
            arr.fbegin()[i] = start + (end - start) * i / (n - 1);
    }

    template <class T, size_t... Dims>
    T product(const MultiArray<T, Dims...> &arr)
    {
        return std::accumulate(arr.fbegin(), arr.fend(), T{1}, std::multiplies<T>());
    }

    template <class T, size_t... Dims>
    T kth_smallest(MultiArray<T, Dims...> arr, size_t k)
    {
        if (k >= arr.size())
            k = arr.size() - 1;
        std::nth_element(arr.fbegin(), arr.fbegin() + k, arr.fend());
        return arr.fbegin()[k];
    }

    template <class T, size_t N>
    double euclidean(const MultiArray<T, N> &a, const MultiArray<T, N> &b)
    {
        double sum = 0;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
        {
            double d = *ai++ - *bi++;
            sum += d * d;
        }
        return std::sqrt(sum);
    }

    template <class T, size_t N>
    double manhattan(const MultiArray<T, N> &a, const MultiArray<T, N> &b)
    {
        double sum = 0;
        auto ai = a.fbegin();
        auto bi = b.fbegin();
        while (ai != a.fend())
            sum += std::abs(*ai++ - *bi++);
        return sum;
    }

    template <class T, size_t N, size_t K>
    MultiArray<T, N + K - 1> convolve1d(const MultiArray<T, N> &signal,
                                        const MultiArray<T, K> &kernel)
    {
        MultiArray<T, N + K - 1> result{};
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < K; j++)
                result[i + j] += signal[i] * kernel[j];
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> sin(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::sin(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> cos(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::cos(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> tan(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::tan(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> asin(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::asin(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> acos(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::acos(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> atan(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::atan(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> sinh(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::sinh(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> cosh(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::cosh(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> tanh(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::tanh(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> exp(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::exp(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> log(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::log(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> log10(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::log10(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> pow(const MultiArray<T, Dims...> &arr, T exponent)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::pow(*ai++, exponent);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> pow(const MultiArray<T, Dims...> &base,
                               const MultiArray<T, Dims...> &exp)
    {
        MultiArray<T, Dims...> result;
        auto bi = base.fbegin();
        auto ei = exp.fbegin();
        auto ri = result.fbegin();
        while (ri != result.fend())
            *ri++ = std::pow(*bi++, *ei++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> floor(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::floor(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> ceil(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::ceil(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    MultiArray<T, Dims...> round(const MultiArray<T, Dims...> &arr)
    {
        MultiArray<T, Dims...> result;
        auto ri = result.fbegin();
        auto ai = arr.fbegin();
        while (ri != result.fend())
            *ri++ = std::round(*ai++);
        return result;
    }

    template <class T, size_t... Dims>
    void print_stats(const MultiArray<T, Dims...> &arr, const char *name = "")
    {
        if (name && *name)
            std::cout << "=== " << name << " ===" << '\n';
        std::cout << "  sum   : " << sum(arr) << '\n';
        std::cout << "  mean  : " << mean(arr) << '\n';
        std::cout << "  min   : " << min(arr) << '\n';
        std::cout << "  max   : " << max(arr) << '\n';
        std::cout << "  stddev: " << stddev(arr) << std::endl;
    }
}
