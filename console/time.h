#pragma once
#include <iostream>
#include <chrono>
#include <cstdint>
#include <utility>
#include <thread>

namespace console
{
    using namespace std;

    class Time
    {
        long double ns_;

    public:
        Time(long double ns) : ns_(ns) {}

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

        friend ostream &operator<<(ostream &os, const Time t)
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
        return Time((long double)(chrono::duration_cast<chrono::nanoseconds>(
                                      chrono::high_resolution_clock::now()
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
        this_thread::sleep_for(chrono::duration<long double>(tr.s()));
    }

    string datetime(const string &fmt = "%Y-%m-%d %H:%M:%S")
    {
        stringstream ss;
        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        tm tm_buffer;
#ifdef _WIN32
        localtime_s(&tm_buffer, &time);
#else
        localtime_r(&time, &tm_buffer);
#endif
        ss << put_time(&tm_buffer, fmt.c_str());
        return ss.str();
    }
}
