#pragma once
#include <iostream>
#include <string>
#include "csexc.h"

namespace console
{
    using namespace std;

    struct JdtSettings
    {
        int len;
        const char *lch, *rch, *fch, *ech, *Ech;
        ostream &os;
    };

    const JdtSettings defaultSettings{50, "[", "]", "#", " ", "\r", cout};
    const JdtSettings simpleSettings{50, "", "", "=", "-", "\r", cout};
    const JdtSettings beautifulSettings{50, "▕", "▏", "█", "░", "\r", cout};

    void jdt(int percent, const JdtSettings &js = defaultSettings)
    {
        if (percent < 0)
            throw jdt_range_error(to_string(percent) + " less than 0");
        if (percent > 100)
            throw jdt_range_error(to_string(percent) + " greater than 100");
        int lct = percent * js.len / 100;
        int rct = js.len - lct;
        js.os << js.lch;
        for (int i = 0; i < lct; i++)
            js.os << js.fch;
        for (int i = 0; i < rct; i++)
            js.os << js.ech;
        js.os
            << js.rch
            << "   "
            << percent
            << '%'
            << js.Ech;
    }
}