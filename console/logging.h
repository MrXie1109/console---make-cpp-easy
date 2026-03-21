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
#include <cstdint>
#include <sstream>
#include "output.h"
#include "colorful.h"
#include "time.h"
#include "strpp.h"
#include "csexc.h"
#include "literals.h"

namespace console
{
    class Logging
    {
    public:
        enum class Level : int8_t
        {
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL
        };

    private:
        Output output;
        bool colorful;
        bool settings[5];

    public:
        void set(Level minLevel)
        {
            int8_t n = int8_t(minLevel);
            for (int i = 0; i < n; i++)
                settings[i] = false;
            for (int i = n; i < 5; i++)
                settings[i] = true;
        }
        void set(bool a, bool b, bool c, bool d, bool e)
        {
            settings[0] = a;
            settings[1] = b;
            settings[2] = c;
            settings[3] = d;
            settings[4] = e;
        }
        Logging(std::ostream &os = std::cout,
                bool cf = false, Level lvl = Level::INFO)
            : output(os, "", "\n", true),
              colorful(cf) { set(lvl); }
        template <class... Args>
        void debug(const Args &...args)
        {
            if (settings[0])
            {
                if (colorful)
                    output(color::BrightBlack,
                           '[', datetime(), "] [DEBUG] - ",
                           args..., color::Reset);
                else
                    output('[', datetime(), "] [DEBUG] - ", args...);
            }
        }
        template <class... Args>
        void info(const Args &...args)
        {
            if (settings[1])
            {
                if (colorful)
                    output(color::BrightCyan,
                           '[', datetime(), "] [.INFO] - ",
                           args..., color::Reset);
                else
                    output('[', datetime(), "] [.INFO] - ", args...);
            }
        }
        template <class... Args>
        void warn(const Args &...args)
        {
            if (settings[2])
            {
                if (colorful)
                    output(color::BrightYellow,
                           '[', datetime(), "] [.WARN] - ",
                           args..., color::Reset);
                else
                    output('[', datetime(), "] [.WARN] - ", args...);
            }
        }
        template <class... Args>
        void error(const Args &...args)
        {
            if (settings[3])
            {
                if (colorful)
                    output(color::BrightRed,
                           '[', datetime(), "] [ERROR] - ",
                           args..., color::Reset);
                else
                    output('[', datetime(), "] [ERROR] - ", args...);
            }
        }
        template <class... Args>
        void fatal(const Args &...args)
        {
            std::string error_info(uni_to_str(args...));
            if (settings[4])
            {
                if (colorful)
                    output(color::BrightMagenta,
                           '[', datetime(), "] [FATAL] - ",
                           error_info, color::Reset);
                else
                    output('[', datetime(), "] [FATAL] - ", error_info);
            }
            throw fatal_logging("Fatal Error: " + error_info);
        }
    } logger(std::cout, true, Logging::Level::INFO);
}
