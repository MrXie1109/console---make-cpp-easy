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
    using namespace std;

    class Path
    {
        string path;

    public:
        using bytes = vector<unsigned char>;

        Path(const string &str) : path(str)
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

        string read_text()
        {
            string text;
            char ch;
            ifstream fin(path);
            if (!fin.is_open())
                throw file_not_found_error("Cannot open " + path);
            while (fin.get(ch))
            {
                text += ch;
            }
            fin.close();
            return text;
        }

        bytes read_binary()
        {
            ifstream fin(path, ios::binary);
            if (!fin.is_open())
                throw file_not_found_error("Cannot open " + path);
            bytes bts{
                istreambuf_iterator<char>(fin),
                (istreambuf_iterator<char>())};
            fin.close();
            return bts;
        }

        vector<string> read_lines()
        {
            return split(read_text(), "\n");
        }

        void write_text(const string &text)
        {
            ofstream fout(path);
            if (!fout.is_open())
                throw file_not_found_error("Cannot open " + path);
            fout << text;
            fout.close();
        }

        void write_binary(const bytes &bts)
        {
            ofstream fout(path, ios::binary);
            if (!fout.is_open())
                throw file_not_found_error("Cannot open " + path);
            fout.write((const char *)(bts.data()), bts.size());
            fout.close();
        }

        void write_lines(const vector<string> &lines)
        {
            ofstream fout(path, ios::binary);
            if (!fout.is_open())
                throw file_not_found_error("Cannot open " + path);
            auto it = lines.begin();
            fout << *it;
            while (++it != lines.end())
                fout << '\n'
                     << *it;
            fout.close();
        }
    };
}