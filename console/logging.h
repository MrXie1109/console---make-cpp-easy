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
        bool &settings(int lvl)
        {
            static bool s[5] = {0, 1, 1, 1, 1};
            return s[lvl];
        }

    public:
        void set(Level minLevel)
        {
            int8_t n = int8_t(minLevel);
            for (int i = 0; i < n; i++)
                settings(i) = false;
            for (int i = n; i < 5; i++)
                settings(i) = true;
        }
        void set(bool a, bool b, bool c, bool d, bool e)
        {
            settings(0) = a;
            settings(1) = b;
            settings(2) = c;
            settings(3) = d;
            settings(4) = e;
        }
        Logging(std::ostream &os = std::cout,
                bool cf = false, Level lvl = Level::INFO)
            : output(os, "", "\n", true),
              colorful(cf) { set(lvl); }
        template <class... Args>
        void debug(const Args &...args)
        {
            if (settings(0))
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
            if (settings(1))
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
            if (settings(2))
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
            if (settings(3))
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
            std::string error_info(uniToStr(args...));
            if (settings(4))
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
