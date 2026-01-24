#pragma once
#include <bits/stdc++.h>

namespace console
{
    class
    {
        std::ostream *os = &std::cout;
        std::string end = "\n";
        std::string sep = " ";

    public:
        void set(std::ostream &Os = std::cout,
                 std::string End = "\n",
                 std::string Sep = " ")
        {
            os = &Os;
            end = End;
            sep = Sep;
        }
        template <class T>
        void operator()(const T &t)
        {
            (*os) << t << end;
        }
        template <class T, class... Args>
        void operator()(const T &t, const Args &...args)
        {
            (*os) << t << sep;
            operator()(args...);
        }
    } print;

    struct TimerResult
    {
        double ns, us, ms, s;
        operator double() const
        {
            return ns;
        }
        TimerResult operator+(const TimerResult &tr) const
        {
            return TimerResult{
                ns + tr.ns,
                us + tr.us,
                ms + tr.ms,
                s + tr.s};
        }
        TimerResult operator-(const TimerResult &tr) const
        {
            return TimerResult{
                ns - tr.ns,
                us - tr.us,
                ms - tr.ms,
                s - tr.s};
        }
        TimerResult operator*(double d) const
        {
            return TimerResult{
                ns * d,
                us * d,
                ms * d,
                s * d};
        }
        TimerResult operator/(double d) const
        {
            return TimerResult{
                ns / d,
                us / d,
                ms / d,
                s / d};
        }
        friend std::ostream &operator<<(std::ostream &os, const TimerResult tr)
        {
            if (tr.s >= 1)
                return os << tr.s << "  s";
            if (tr.ms >= 1)
                return os << tr.ms << " ms";
            if (tr.us >= 1)
                return os << tr.us << " μs";
            return os << tr.ns << " ns";
        }
    };

    template <class T>
    bool save(const T &data, const char *path)
    {
        std::ofstream file(path);
        if (!file)
            return false;
        file.write((const char *)(&data), sizeof(data));
        return file.good();
    }

    template <class T>
    bool load(T &data, const char *path)
    {
        std::ifstream file(path);
        if (!file)
            return false;
        file.read((char *)(&data), sizeof(data));
        return file.good();
    }

    std::string ltrim(std::string str)
    {
        auto it = std::find_if(str.begin(), str.end(),
                               [](unsigned char c)
                               { return !std::isspace(c); });
        str.erase(str.begin(), it);
        return str;
    }

    std::string rtrim(std::string str)
    {
        auto it = std::find_if(str.rbegin(), str.rend(),
                               [](unsigned char c)
                               { return !std::isspace(c); });
        str.erase(it.base(), str.end());
        return str;
    }

    std::string trim(std::string str)
    {
        return ltrim(rtrim(str));
    }

    std::string upper(std::string str)
    {
        for (char &ch : str)
        {
            if (ch >= 'a' && ch <= 'z')
                ch += 'A' - 'a';
        }
        return str;
    }

    std::string lower(std::string str)
    {
        for (char &ch : str)
        {
            if (ch >= 'A' && ch <= 'Z')
                ch -= 'A' - 'a';
        }
        return str;
    }

    std::string title(std::string str)
    {
        if (str[0] >= 'a' && str[0] <= 'z')
            str[0] += 'A' - 'a';
        for (std::size_t i = 1; i < str.size(); ++i)
        {
            if (std::isspace(str[i - 1]) && str[i] >= 'a' && str[i] <= 'z')
                str[i] += 'A' - 'a';
            else if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] -= 'A' - 'a';
        }
        return str;
    }

    inline TimerResult now()
    {
        int64_t tmp = std::chrono::system_clock::now()
                          .time_since_epoch()
                          .count();
        return TimerResult{(double)tmp, (double)tmp / 1e3,
                           (double)tmp / 1e6, (double)tmp / 1e9};
    }

    template <class F, class... Args>
    TimerResult timer(F f, const Args &...args)
    {
        TimerResult start = now();
        f(args...);
        return now() - start;
    }

    void sleep(double s)
    {
        std::this_thread::sleep_for(
            std::chrono::duration<double>(s));
    }

    int randomint(int min, int max)
    {
        static std::mt19937 gen(now());
        return std::uniform_int_distribution<>(min, max)(gen);
    }

    double uniform(double min, double max)
    {
        static std::mt19937 gen(now());
        return std::uniform_real_distribution<>(min, max)(gen);
    }

    template <class T>
    auto choice(const T &container) -> decltype(container[0])
    {
        if (container.size() <= 0)
            throw std::invalid_argument(
                "console::choice: Cannot choose from an empty container");
        return container[randomint(0, container.size() - 1)];
    }
}