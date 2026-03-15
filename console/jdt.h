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
#include "csexc.h"

namespace console
{
    struct JdtSettings
    {
        int len;
        const char *lch, *rch, *fch, *ech, *Ech;
        std::ostream &os;
    };

    const JdtSettings normalSettings{50, "[", "]", "#", " ", "\r", std::cout};
    const JdtSettings simpleSettings{50, "", "", "=", "-", "\r", std::cout};
    const JdtSettings beautifulSettings{
        50,
        "\u2595", // "▕"
        "\u258F", // "▏"
        "\u2588", // "█"
        "\u2591", // "░"
        "\r",
        std::cout};
    /**
     * 注：如果编译器可以识别字面值但无法识别码点
     *     可以手动将码点替换为对应的字符
     *     如果均无法识别
     *     请勿使用beautifulSettings */

    JdtSettings defaultSettings = normalSettings;

    void jdt(int percent, const JdtSettings &js = defaultSettings)
    {
        if (percent < 0)
            throw jdt_range_error(std::to_string(percent) + " less than 0");
        if (percent > 100)
            throw jdt_range_error(std::to_string(percent) + " greater than 100");
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
