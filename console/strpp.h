#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>

namespace console
{
    using namespace std;

    string ltrim(string str)
    {
        auto it = find_if(str.begin(), str.end(),
                          [](unsigned char c)
                          { return !isspace(c); });
        str.erase(str.begin(), it);
        return str;
    }

    string rtrim(string str)
    {
        auto it = find_if(str.rbegin(), str.rend(),
                          [](unsigned char c)
                          { return !isspace(c); });
        str.erase(it.base(), str.end());
        return str;
    }

    string trim(string str)
    {
        return ltrim(rtrim(str));
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
            text.substr(pos, sep.size()),
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
        stringstream ss;
        ss << t;
        return ss.str();
    }
}