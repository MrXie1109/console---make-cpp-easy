#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
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
            std::string text;
            char ch;
            std::ifstream fin(path);
            if (!fin.is_open())
                throw file_not_found_error("Cannot open " + path);
            while (fin.get(ch))
            {
                text += ch;
            }
            fin.close();
            return text;
        }

        Bytes read_binary()
        {
            std::ifstream fin(path, std::ios::binary);
            if (!fin.is_open())
                throw file_not_found_error("Cannot open " + path);
            Bytes bytes{
                std::istreambuf_iterator<char>(fin),
                (std::istreambuf_iterator<char>())};
            fin.close();
            return bytes;
        }

        std::vector<std::string> read_lines()
        {
            return split(read_text(), "\n");
        }

        void write_text(const std::string &text)
        {
            std::ofstream fout(path);
            if (!fout.is_open())
                throw file_not_found_error("Cannot open " + path);
            fout << text;
            fout.close();
        }

        void write_binary(const Bytes &bts)
        {
            std::ofstream fout(path, std::ios::binary);
            if (!fout.is_open())
                throw file_not_found_error("Cannot open " + path);
            fout.write((const char *)(bts.data()), bts.size());
            fout.close();
        }

        void write_lines(const std::vector<std::string> &lines)
        {
            std::ofstream fout(path, std::ios::binary);
            if (!fout.is_open())
                throw file_not_found_error("Cannot open " + path);
            auto it = lines.begin();
            fout << *it;
            while (++it != lines.end())
                fout << '\n'
                     << *it;
            fout.close();
        }

        bool exists()
        {
            return std::ifstream(path).is_open();
        }

        void touch()
        {
            std::ofstream(path);
        }

        void ensure()
        {
            std::ofstream(path, std::ios::app);
        }
    };
}
