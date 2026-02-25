#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <cfloat>
#include <cstdint>
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
            is.os << prompt << flush;
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
        is.os << prompt << flush;
        if (is.is.peek() == '\n')
            is.is.get();
        getline(is.is, tmp);
        return tmp;
    }

    long double inputWithRange(const string &prompt = "Type a number: ",
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
        is.os << prompt << flush;
        char tmp = is.is.get();
        is.is.ignore(numeric_limits<streamsize>::max(), '\n');
        return tmp;
    }

    bool inputYesOrNo(const string &prompt = "Type yes or no: ",
                      const InputSettings &is = inputSettings)
    {
        string tmp;
        while (true)
        {
            char tmp = inputChar(prompt, is);
            if (tmp == 'Y' || tmp == 'y')
                return true;
            else if (tmp == 'N' || tmp == 'n')
                return false;
            else
                is.os << "Please type yes or no." << endl;
        }
    }
}