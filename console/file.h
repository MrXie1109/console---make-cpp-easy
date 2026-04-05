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
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <type_traits>
#include "csexc.h"
#include "strpp.h"

namespace console
{
    class Path
    {
        std::string path;

    public:
        using Bytes = std::vector<unsigned char>;

        Path(const std::string &str) : path(str)
        {
#ifdef _WIN32
            for (char &ch : path)
            {
                if (ch == '/')
                    ch = '\\';
            }
#endif
        }

        friend Path operator/(const Path &p1, const Path &p2)
        {
            return p1.path + '/' + p2.path;
        }

        std::string read_text()
        {
            std::ifstream fin(path);
            if (!fin.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            std::string text{
                std::istreambuf_iterator<char>(fin),
                std::istreambuf_iterator<char>()};
            if (!fin.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
            return text;
        }

        Bytes read_binary()
        {
            std::ifstream fin(path, std::ios::binary);
            if (!fin.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            Bytes bytes{
                std::istreambuf_iterator<char>(fin),
                std::istreambuf_iterator<char>()};
            if (!fin.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
            return bytes;
        }

        std::vector<std::string> read_lines()
        {
            return split(read_text(), "\n");
        }

        template <class T>
        T read_POD()
        {
            static_assert(std::is_trivially_copyable<T>::value,
                          "This Type is Not POD Type!");
            std::ifstream fin(path, std::ios::binary);
            if (!fin.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            T data;
            fin.read((char *)(&data), sizeof(data));
            if (!fin.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
            return data;
        }

        template <class T>
        T unsafe_read_POD()
        {
            std::ifstream fin(path, std::ios::binary);
            if (!fin.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            T data;
            fin.read((char *)(&data), sizeof(data));
            if (!fin.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
            return data;
        }

        void write_text(const std::string &text)
        {
            std::ofstream fout(path);
            if (!fout.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            fout << text;
            if (!fout.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
        }

        void write_binary(const Bytes &bts)
        {
            std::ofstream fout(path, std::ios::binary);
            if (!fout.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            fout.write((const char *)(bts.data()), bts.size());
            if (!fout.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
        }

        void write_lines(const std::vector<std::string> &lines)
        {
            std::ofstream fout(path, std::ios::binary);
            if (lines.empty())
                return;
            if (!fout.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            auto it = lines.begin();
            fout << *it;
            while (++it != lines.end())
                fout << '\n'
                     << *it;
            if (!fout.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
        }

        template <class T>
        void write_POD(const T &data)
        {
            static_assert(std::is_trivially_copyable<T>::value,
                          "This Type is Not POD Type!");
            std::ofstream fout(path, std::ios::binary);
            if (!fout.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            fout.write((const char *)(&data), sizeof(data));
            if (!fout.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
        }

        template <class T>
        void unsafe_write_POD(const T &data)
        {
            std::ofstream fout(path, std::ios::binary);
            if (!fout.is_open())
                throw file_error("Cannot Open File \"" + path + '"');
            fout.write((const char *)(&data), sizeof(data));
            if (!fout.good())
                throw file_error("The Stream of \"" + path + "\" is Not Good");
        }

        bool exists()
        {
            return std::ifstream{path}.is_open();
        }

        void touch()
        {
            std::ofstream{path};
        }

        void ensure()
        {
            std::ofstream{path, std::ios::app};
        }
    };
}
