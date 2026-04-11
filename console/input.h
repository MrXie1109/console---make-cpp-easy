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
#include <string>
#include <limits>
#include <cfloat>
#include <cstdint>
#include "strpp.h"

namespace console
{
    struct InputSettings
    {
        std::ostream &os;
        std::istream &is;
    } inputSettings{std::cout, std::cin};

    template <class T = std::string>
    T input(const std::string &prompt = "",
            const InputSettings &is = inputSettings)
    {
        T tmp;
        std::string message;
        while (true)
        {
            is.os << prompt << std::flush;
            is.is >> tmp;
            if (!is.is)
            {
                is.is.clear();
                is.is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                is.os << "StreamError!\n";
                continue;
            }
            is.is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return tmp;
        }
    }

    long double inputNumber(const std::string &prompt = "Type a number: ",
                            const InputSettings &is = inputSettings)
    {
        return input<long double>(prompt, is);
    }

    std::string inputLine(const std::string &prompt = "Type a line string: ",
                          const InputSettings &is = inputSettings)
    {
        std::string tmp;
        is.os << prompt << std::flush;
        if (is.is.peek() == '\n')
            is.is.get();
        std::getline(is.is, tmp);
        return tmp;
    }

    long double inputWithRange(const std::string &prompt = "Type a number: ",
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
                is.os << "less than the minimum value of " << min << std::endl;
                continue;
            }
            if (tmp > max)
            {
                is.os << "Greater than the maximum value of "
                      << max << std::endl;
                continue;
            }
            return tmp;
        }
    }

    char inputChar(const std::string &prompt = "Type a character: ",
                   const InputSettings &is = inputSettings)
    {
        is.os << prompt << std::flush;
        char tmp = is.is.get();
        is.is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return tmp;
    }

    bool inputYesOrNo(const std::string &prompt = "Type yes or no: ",
                      const InputSettings &is = inputSettings)
    {
        std::string tmp;
        while (true)
        {
            char tmp = inputChar(prompt, is);
            if (tmp == 'Y' || tmp == 'y')
                return true;
            else if (tmp == 'N' || tmp == 'n')
                return false;
            else
                is.os << "Please type yes or no." << std::endl;
        }
    }

    std::string inputAll(const std::string &prompt = "",
                         const InputSettings &is = inputSettings)
    {
        return {std::istreambuf_iterator<char>(is.is),
                std::istreambuf_iterator<char>()};
    }
}
