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
    std::string ltrim(std::string str)
    {
        auto it = std::find_if(str.begin(), str.end(),
                               [](unsigned char uc) -> bool
                               { return !isspace(uc); });
        str.erase(str.begin(), it);
        return str;
    }

    std::string rtrim(std::string str)
    {
        auto it = std::find_if(str.rbegin(), str.rend(),
                               [](unsigned char uc) -> bool
                               { return !isspace(uc); });
        str.erase(it.base(), str.end());
        return str;
    }

    std::string trim(std::string str)
    {
        return ltrim(rtrim(str));
    }

    std::string ltrim(std::string str, const std::string &chars)
    {
        auto it = std::find_if(str.begin(), str.end(),
                               [&chars](unsigned char ch)
                               {
                                   return chars.find(ch) == std::string::npos;
                               });
        str.erase(str.begin(), it);
        return str;
    }

    std::string rtrim(std::string str, const std::string &chars)
    {
        auto it = std::find_if(str.rbegin(), str.rend(),
                               [&chars](unsigned char ch)
                               {
                                   return chars.find(ch) == std::string::npos;
                               });
        str.erase(it.base(), str.end());
        return str;
    }

    std::string trim(std::string str, const std::string &chars)
    {
        return ltrim(rtrim(str, chars), chars);
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
        if (str.empty())
            return "";
        if (str[0] >= 'a' && str[0] <= 'z')
            str[0] += 'A' - 'a';
        for (size_t i = 1; i < str.size(); ++i)
        {
            if (isspace((unsigned char)str[i - 1]) &&
                str[i] >= 'a' && str[i] <= 'z')
                str[i] += 'A' - 'a';
            else if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] -= 'A' - 'a';
        }
        return str;
    }

    struct PartitionResult
    {
        std::string left;
        std::string middle;
        std::string right;
        friend std::ostream &operator<<(
            std::ostream &os, const PartitionResult &pr)
        {
            return os << "(\"" << pr.left << "\", \"" << pr.middle
                      << "\", \"" << pr.right << "\")";
        }
    };

    PartitionResult partition(
        const std::string &text, const std::string &sep)
    {
        size_t pos = text.find(sep);
        if (pos == std::string::npos)
            return PartitionResult{text, "", ""};
        return PartitionResult{
            text.substr(0, pos),
            sep,
            text.substr(pos + sep.size())};
    }

    std::vector<std::string> split(
        std::string text, const std::string &sep = " ")
    {
        std::vector<std::string> vec;
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
    std::string join(
        const std::vector<T> &vec, const std::string &sep = "")
    {
        if (vec.empty())
            return "";
        std::stringstream ss;
        auto it = vec.begin();
        ss << *it;
        while (++it != vec.end())
        {
            ss << sep << *it;
        }
        return ss.str();
    }

    template <class... Args>
    std::string uni_to_str(Args &&...args)
    {
        std::ostringstream oss;
        int _[] = {0, (oss << std::forward<Args>(args), 0)...};
        (void)_;
        return oss.str();
    }

    class f_string : public std::string
    {
    public:
        using std::string::string;

        template <class T>
        f_string operator%(const T &t)
        {
            auto result = partition(*this, "{}");
            if (result.middle == "{}")
            {
                return result.left + uni_to_str(t) + result.right;
            }
            throw bad_format("Bad Format");
        }
    };
}
