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
}
