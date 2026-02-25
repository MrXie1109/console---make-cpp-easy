#pragma once
#include <iostream>
#include <chrono>
#include <cstdint>
#include <utility>
#include <thread>

namespace console
{
    using namespace std;

    struct Time
    {
        long double ns, us, ms, s;

        Time(long double NS)
        {
            ns = NS;
            us = ns / 1000;
            ms = us / 1000;
            s = ms / 1000;
        }
        operator long double() const
        {
            return ns;
        }
        friend ostream &operator<<(ostream &os, const Time t)
        {
            if (t.s >= 1)
                return os << t.s << " s";
            if (t.ms >= 1)
                return os << t.ms << "ms";
            if (t.us >= 1)
                return os << t.us << "μs";
            return os << t.ns << "ns";
        }
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
        this_thread::sleep_for(chrono::duration<long double>(tr.s));
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