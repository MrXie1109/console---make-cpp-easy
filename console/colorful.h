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

namespace console
{
    namespace color
    {
        const char
            *Black = "\033[30m",
            *Red = "\033[31m",
            *Green = "\033[32m",
            *Yellow = "\033[33m",
            *Blue = "\033[34m",
            *Magenta = "\033[35m",
            *Cyan = "\033[36m",
            *White = "\033[37m",
            *BrightBlack = "\033[90m",
            *BrightRed = "\033[91m",
            *BrightGreen = "\033[92m",
            *BrightYellow = "\033[93m",
            *BrightBlue = "\033[94m",
            *BrightMagenta = "\033[95m",
            *BrightCyan = "\033[96m",
            *BrightWhite = "\033[97m",
            *Reset = "\033[0m";

        const char
            *BgBlack = "\033[40m",
            *BgRed = "\033[41m",
            *BgGreen = "\033[42m",
            *BgYellow = "\033[43m",
            *BgBlue = "\033[44m",
            *BgMagenta = "\033[45m",
            *BgCyan = "\033[46m",
            *BgWhite = "\033[47m",
            *BgBrightBlack = "\033[100m",
            *BgBrightRed = "\033[101m",
            *BgBrightGreen = "\033[102m",
            *BgBrightYellow = "\033[103m",
            *BgBrightBlue = "\033[104m",
            *BgBrightMagenta = "\033[105m",
            *BgBrightCyan = "\033[106m",
            *BgBrightWhite = "\033[107m";

        const char
            *Bold = "\033[1m",
            *Dim = "\033[2m",
            *Italic = "\033[3m",
            *Underline = "\033[4m",
            *Blink = "\033[5m",
            *Reverse = "\033[7m",
            *Hidden = "\033[8m",
            *Strikethrough = "\033[9m";
    }
}
