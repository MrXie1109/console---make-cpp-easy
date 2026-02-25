#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <initializer_list>
#include <utility>
#include <cstdint>
#include "output.h"
#include "csexc.h"

namespace console
{
    using namespace std;

    template <class F>
    string ltrim(string str, F &&f = [](unsigned char c)
                             { return !isspace(c); })
    {
        auto it = find_if(str.begin(), str.end(), f);
        str.erase(str.begin(), it);
        return str;
    }

    template <class F>
    string rtrim(string str, F &&f = [](unsigned char c)
                             { return !isspace(c); })
    {
        auto it = find_if(str.rbegin(), str.rend(), f);
        str.erase(it.base(), str.end());
        return str;
    }

    template <class F>
    string trim(string str, F &&f = [](unsigned char c)
                            { return !isspace(c); })
    {
        return ltrim(rtrim(str, f), f);
    }

    string upper(string str)
    {
        for (char &ch : str)
        {
            if (ch >= 'a' && ch <= 'z')
                ch += 'A' - 'a';
        }
        return str;
    }

    string lower(string str)
    {
        for (char &ch : str)
        {
            if (ch >= 'A' && ch <= 'Z')
                ch -= 'A' - 'a';
        }
        return str;
    }

    string title(string str)
    {
        if (str[0] >= 'a' && str[0] <= 'z')
            str[0] += 'A' - 'a';
        for (size_t i = 1; i < str.size(); ++i)
        {
            if (isspace(str[i - 1]) && str[i] >= 'a' && str[i] <= 'z')
                str[i] += 'A' - 'a';
            else if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] -= 'A' - 'a';
        }
        return str;
    }

    struct PartitionResult
    {
        string left;
        string middle;
        string right;
        friend ostream &operator<<(
            ostream &os, const PartitionResult &pr)
        {
            return os << '(' << pr.left << ", " << pr.middle
                      << ", " << pr.right << ')';
        }
    };

    PartitionResult partition(
        const string &text, const string &sep)
    {
        size_t pos = text.find(sep);
        if (pos == string::npos)
            return PartitionResult{text, "", ""};
        return PartitionResult{
            text.substr(0, pos),
            sep,
            text.substr(pos + sep.size())};
    }

    vector<string> split(
        string text, const string &sep = " ")
    {
        vector<string> vec;
        PartitionResult pr;
        while ((pr = partition(text, sep)).middle != "")
        {
            vec.push_back(pr.left);
            text = pr.right;
        }
        vec.push_back(pr.left);
        return vec;
    }

    template <class T>
    string join(
        const vector<T> &vec, const string &sep = "")
    {
        if (vec.empty())
            return "";
        stringstream ss;
        auto it = vec.begin();
        ss << *it;
        while (++it != vec.end())
        {
            ss << sep << *it;
        }
        return ss.str();
    }

    template <class T>
    string uniToStr(T &&t)
    {
        ostringstream oss;
        oss << t;
        return oss.str();
    }

    class f_string : public string
    {
    public:
        template <class... Args>
        f_string(Args &&...args) : string(forward<Args>(args)...) {}
        template <class T>
        f_string operator%(const T &t)
        {
            auto result = partition(*this, "{}");
            if (result.middle == "{}")
            {
                return result.left + uniToStr(t) + result.right;
            }
            throw bad_format("Bad Format");
        }
    };
}