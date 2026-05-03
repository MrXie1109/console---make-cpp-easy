/**
 * @file kb.h
 * @brief 非阻塞的获取键盘的按键输入。
 * @details 使用条件编译确保在不同平台可以使用统一的 API，但只能检测常见的按键情况。
 *          不处理边界情况，可以用于中小型程序，但切勿在生产环境使用。
 * @author MrXie1109
 * @date 2026
 * @copyright MIT License
 */

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
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <poll.h>
#endif

namespace console
{
    /**
     * @enum Key
     * @brief 用于表示常用按键的枚举。
     */
    enum class Key : int
    {
        None = 0,

        A = 'A',
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Num0 = '0',
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        Space = ' ',

        Enter = 13,
        Esc = 27,
        Backspace = 127,
        Tab = 9,

        Up = 1000,
        Down,
        Left,
        Right,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
    };

    /**
     * @class Keyboard
     * @brief 用于监视键盘键击情况的类。
     */
    class Keyboard
    {
    public:
        /**
         * @brief 构造函数，开始监视键盘键击。
         * @warning 在 Keyboard 的生命周期内，stdin 将处于不可用状态。
         */
        Keyboard()
        {
#ifdef _WIN32
            hStdin = GetStdHandle(STD_INPUT_HANDLE);
            GetConsoleMode(hStdin, &oldMode);
            SetConsoleMode(hStdin, oldMode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
#else
            tcgetattr(STDIN_FILENO, &oldTio);
            struct termios newTio = oldTio;
            newTio.c_lflag &= ~(ICANON | ECHO);
            newTio.c_cc[VMIN] = 0;
            newTio.c_cc[VTIME] = 0;
            tcsetattr(STDIN_FILENO, TCSANOW, &newTio);
#endif
        }

        /**
         * @brief 析构函数，结束对键盘键击的监视。
         * @note stdin 将恢复可用状态。
         */
        ~Keyboard()
        {
#ifdef _WIN32
            SetConsoleMode(hStdin, oldMode);
#else
            tcsetattr(STDIN_FILENO, TCSANOW, &oldTio);
#endif
        }

        /// @brief 被删除的拷贝构造函数
        Keyboard(const Keyboard &) = delete;

        /// @brief 被删除的移动构造函数
        Keyboard(Keyboard &&) = delete;

        /// @brief 被删除的拷贝赋值
        Keyboard &operator=(const Keyboard &) = delete;

        /// @brief 被删除的移动赋值
        Keyboard &operator=(Keyboard &&) = delete;

        /**
         * @brief 试图取得当前键击的按键。
         * @return Key 如果没有键击，返回 Key::None，否则返回对应按键。
         */
        Key get()
        {
            int raw = readRaw();
            if (raw == -1)
                return Key::None;
            return parse(raw);
        }

        /**
         * @brief 等待直到键击并取得当前按键。
         * @return Key 返回对应按键。
         */
        Key wait()
        {
            while (true)
            {
                int raw = readRawBlock();
                if (raw != -1)
                    return parse(raw);
            }
        }

    private:
#ifdef _WIN32
        HANDLE hStdin; ///< Windows: 标准输入设备句柄（STD_INPUT_HANDLE）
        DWORD oldMode; ///< Windows: 原始控制台输入模式（用于析构时恢复）
#else
        struct termios oldTio; ///< Linux/Unix: 原始终端I/O属性（用于析构时恢复规范模式与回显）
#endif

        /**
         * @brief 读取一个原始按键值（非阻塞）。
         * @return 如果按键存在，返回按键的整数扫描码；否则返回 -1。
         * @details Windows 平台使用 _kbhit() 和 _getch()；
         *          Linux 平台使用 poll() 和 read()。
         */
        int readRaw()
        {
#ifdef _WIN32
            if (_kbhit())
                return _getch();
            return -1;
#else
            struct pollfd pfd = {STDIN_FILENO, POLLIN, 0};
            if (poll(&pfd, 1, 0) <= 0)
                return -1;
            unsigned char c;
            if (read(STDIN_FILENO, &c, 1) != 1)
                return -1;
            return c;
#endif
        }

        /**
         * @brief 读取一个原始按键值（阻塞）。
         * @return 按键的整数扫描码。
         * @details Windows 平台直接调用 _getch()；
         *          Linux 平台循环调用 read() 直到成功读取一个字节。
         */
        int readRawBlock()
        {
#ifdef _WIN32
            return _getch();
#else
            unsigned char c;
            struct pollfd pfd = {STDIN_FILENO, POLLIN, 0};
            while (true)
            {
                if (poll(&pfd, 1, -1) > 0)
                {
                    if (read(STDIN_FILENO, &c, 1) == 1)
                        return c;
                }
            }
#endif
        }

        /**
         * @brief 将原始扫描码解析为 Key 枚举值。
         * @param raw 原始按键整数值（来自 readRaw 或 readRawBlock）。
         * @return 对应的 Key 枚举值；若无法识别则返回 Key::None。
         * @details 处理以下情况：
         *          - 字母字符（自动将小写转为大写）
         *          - 数字字符
         *          - 空格、回车、Esc、退格、Tab
         *          - Windows 平台扩展键（方向键、F1-F12，其扫描码为 0xE0 或 0x00）
         *          - 其他平台无法识别的键返回 None
         */
        Key parse(int raw)
        {
            if ((raw >= 'A' && raw <= 'Z') || (raw >= '0' && raw <= '9'))
            {
                return static_cast<Key>(raw);
            }
            if (raw >= 'a' && raw <= 'z')
            {
                return static_cast<Key>(raw - 32);
            }
            switch (raw)
            {
            case ' ':
                return Key::Space;
            case 13:
                return Key::Enter;
            case 27:
                return handleEscape();
            case 8:
            case 127:
                return Key::Backspace;
            case 9:
                return Key::Tab;
            }
#ifdef _WIN32
            if (raw == 0xE0 || raw == 0x00)
            {
                int ext = _getch();
                switch (ext)
                {
                case 0x48:
                    return Key::Up;
                case 0x50:
                    return Key::Down;
                case 0x4B:
                    return Key::Left;
                case 0x4D:
                    return Key::Right;
                case 0x3B:
                    return Key::F1;
                case 0x3C:
                    return Key::F2;
                case 0x3D:
                    return Key::F3;
                case 0x3E:
                    return Key::F4;
                case 0x3F:
                    return Key::F5;
                case 0x40:
                    return Key::F6;
                case 0x41:
                    return Key::F7;
                case 0x42:
                    return Key::F8;
                case 0x43:
                    return Key::F9;
                case 0x44:
                    return Key::F10;
                case 0x85:
                    return Key::F11;
                case 0x86:
                    return Key::F12;
                }
            }
#endif
            return Key::None;
        }

        /**
         * @brief 处理以 ESC (27) 开头的转义序列（主要针对 Linux 终端）。
         * @return 如果识别为方向键则返回对应 Key；否则返回 Key::Esc。
         * @details 在 Linux 终端下，方向键会发送 "\033[A"、"\033[B" 等三字节序列。
         *          本函数通过非阻塞 poll 检查后续输入，若在 5ms 内读到 "[A"-"[D]"
         *          则转为方向键，否则视为普通 Esc 键。
         */
        Key handleEscape()
        {
#ifndef _WIN32
            struct pollfd pfd = {STDIN_FILENO, POLLIN, 0};
            if (poll(&pfd, 1, 5) <= 0)
                return Key::Esc;
            char seq[3];
            int n = read(STDIN_FILENO, seq, 3);
            if (n >= 2 && seq[0] == '[')
            {
                switch (seq[1])
                {
                case 'A':
                    return Key::Up;
                case 'B':
                    return Key::Down;
                case 'C':
                    return Key::Right;
                case 'D':
                    return Key::Left;
                }
            }
#endif
            return Key::Esc;
        }
    };
}
