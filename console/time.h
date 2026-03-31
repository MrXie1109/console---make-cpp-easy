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
#include <iostream>
#include <chrono>
#include <cstdint>
#include <utility>
#include <thread>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace console
{
    class Time
    {
        long double ns_;

    public:
        Time(long double ns = 0) : ns_(ns) {}

        operator long double() const
        {
            return ns_;
        }

        long double ns() const { return ns_; }
        long double us() const { return ns_ / 1e3; }
        long double ms() const { return ns_ / 1e6; }
        long double s() const { return ns_ / 1e9; }
        long double min() const { return ns_ / 60 / 1e9; }
        long double hr() const { return ns_ / 3600 / 1e9; }

        friend std::ostream &operator<<(std::ostream &os, const Time t)
        {
            if (t.ns_ > 3600 * 1e9)
                return os << t.ns_ / 3600 / 1e9 << "hr";
            if (t.ns_ > 60 * 1e9)
                return os << t.ns_ / 60 / 1e9 << "min";
            if (t.ns_ > 1e9)
                return os << t.ns_ / 1e9 << "s";
            if (t.ns_ > 1e6)
                return os << t.ns_ / 1e6 << "ms";
            if (t.ns_ > 1e3)
                return os << t.ns_ / 1e3 << "μs";
            return os << t.ns_ << "ns";
        }

        friend Time operator+(Time t1, Time t2) { return t1.ns_ + t2.ns_; }
        friend Time operator-(Time t1, Time t2) { return t1.ns_ - t2.ns_; }
        Time operator*(long double d) const { return ns_ * d; }
        Time operator/(long double d) const { return ns_ / d; }

        friend bool operator==(Time t1, Time t2) { return t1.ns_ == t2.ns_; }
        friend bool operator!=(Time t1, Time t2) { return t1.ns_ != t2.ns_; }
        friend bool operator<(Time t1, Time t2) { return t1.ns_ < t2.ns_; }
        friend bool operator>(Time t1, Time t2) { return t1.ns_ > t2.ns_; }
        friend bool operator<=(Time t1, Time t2) { return t1.ns_ <= t2.ns_; }
        friend bool operator>=(Time t1, Time t2) { return t1.ns_ >= t2.ns_; }
    };

    Time now()
    {
        return Time((long double)(std::chrono::
                                      duration_cast<std::chrono::nanoseconds>(
                                          std::chrono::high_resolution_clock::
                                              now()
                                                  .time_since_epoch())
                                          .count()));
    }

    template <class F, class... Args>
    Time timer(F &&f, Args &&...args)
    {
        Time start = now();
        f(args...);
        return now() - start;
    }

    void sleep(const Time &tr)
    {
        std::this_thread::sleep_for(std::chrono::duration<long double>(tr.s()));
    }

    std::string datetime(const std::string &fmt = "%Y-%m-%d %H:%M:%S")
    {
        std::stringstream ss;
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buffer;
#ifdef _WIN32
        localtime_s(&tm_buffer, &time);
#else
        localtime_r(&time, &tm_buffer);
#endif
        ss << std::put_time(&tm_buffer, fmt.c_str());
        return ss.str();
    }
}
