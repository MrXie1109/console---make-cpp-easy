#pragma once
#include <iostream>
#include <string>
#include <climits>
#include <cfloat>
#include "strpp.h"

namespace console
{
    using namespace std;

    struct InputSettings
    {
        ostream &os;
        istream &is;
    } inputSettings{cout, cin};

    template <class T = string>
    T input(const string &prompt = "", const InputSettings &is = inputSettings)
    {
        T tmp;
        string message;
        while (true)
        {
            is.os << prompt;
            is.is >> tmp;
            if (!is.is)
            {
                is.is.clear();
                is.is.ignore(numeric_limits<streamsize>::max(), '\n');
                is.os << "StreamError!\n";
                continue;
            }
            is.is.ignore(numeric_limits<streamsize>::max(), '\n');
            return tmp;
        }
    }

    long double inputNumber(const string &prompt = "Type a number: ",
                            const InputSettings &is = inputSettings)
    {
        return input<long double>(prompt, is);
    }

    string inputLine(const string &prompt = "Type a line string: ",
                     const InputSettings &is = inputSettings)
    {
        string tmp;
        is.os << prompt;
        getline(is.is, tmp);
        return tmp;
    }

    bool inputYesOrNo(const string &prompt = "Type yes or no: ",
                      const InputSettings &is = inputSettings)
    {
        string tmp;
        while (true)
        {
            tmp = lower(input<string>(prompt, is));
            if (tmp == "yes" || tmp == "y")
                return true;
            if (tmp == "no" || tmp == "n")
                return false;
            is.os << "Please type yes of no.\n";
        }
    }

    long double inputWithRange(const string &prompt = "Type yes or no: ",
                               long double min = DBL_MIN,
                               long double max = DBL_MAX,
                               const InputSettings &is = inputSettings)
    {
        long double tmp;
        while (true)
        {
            tmp = input<long double>(prompt, is);
            if (tmp < min)
            {
                is.os << "less than the minimum value of " << min << endl;
                continue;
            }
            if (tmp > max)
            {
                is.os << "Greater than the maximum value of " << max << endl;
                continue;
            }
            return tmp;
        }
    }

    char inputChar(const string &prompt = "Type a character: ",
                   const InputSettings &is = inputSettings)
    {
        is.os << prompt;
        char tmp = is.is.get();
        is.is.ignore(numeric_limits<streamsize>::max(), '\n');
        return tmp;
    }

    template <class T>
    T &inputChoice(vector<T> &vec,
                   const string &prompt = "Type your choice: ",
                   const InputSettings &is = inputSettings)
    {
        size_t index;
        for (size_t i = 0; i < vec.size(); i++)
        {
            is.os << i + 1 << ": " << vec[i] << '\n';
        }
        while (true)
        {
            index = input<size_t>(prompt, is);
            if (index >= 1 && index <= vec.size())
                return vec[index - 1];
            is.os << "Out of range.\n";
        }
    }

    template <class T>
    const T &inputChoice(const vector<T> &vec,
                         const string &prompt = "Type your choice: ",
                         const InputSettings &is = inputSettings)
    {
        size_t index;
        for (size_t i = 0; i < vec.size(); i++)
        {
            is.os << i + 1 << ": " << vec[i] << '\n';
        }
        while (true)
        {
            index = input<size_t>(prompt, is);
            if (index >= 1 && index <= vec.size())
                return vec[index - 1];
            is.os << "Out of range.\n";
        }
    }
}