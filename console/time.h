#pragma once
#include <iostream>
#include <chrono>
#include <cstdint>
#include <utility>
#include <thread>

namespace console
{
    using namespace std;

    struct TimerResult
    {
        double ns, us, ms, s;

        TimerResult(double NS)
        {
            ns = NS;
            us = ns / 1000;
            ms = us / 1000;
            s = ms / 1000;
        }
        operator double() const
        {
            return ns;
        }
        friend ostream &operator<<(ostream &os, const TimerResult tr)
        {
            if (tr.s >= 1)
                return os << tr.s << " s";
            if (tr.ms >= 1)
                return os << tr.ms << "ms";
            if (tr.us >= 1)
                return os << tr.us << "μs";
            return os << tr.ns << "ns";
        }
    };

    TimerResult now()
    {
        return TimerResult(double(chrono::duration_cast<chrono::nanoseconds>(
                                      chrono::high_resolution_clock::now()
                                          .time_since_epoch())
                                      .count()));
    }

    template <class F, class... Args>
    TimerResult timer(F &&f, Args &&...args)
    {
        TimerResult start = now();
        f(args...);
        return now() - start;
    }

    void sleep(double s)
    {
        this_thread::sleep_for(chrono::duration<double>(s));
    }

    void sleep(const TimerResult &tr)
    {
        this_thread::sleep_for(chrono::duration<double>(tr.s));
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