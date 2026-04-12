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
#include <iterator>
#include "csexc.h"

namespace console
{

    struct ProgressConfig
    {
        std::ostream &os;
        int width;
        std::string fill_char;
        std::string empty_char;
        std::string prefix;
        std::string suffix;
        bool show_percent;

        ProgressConfig(std::ostream &o = std::cout, int w = 50,
                       std::string fc = "#", std::string ec = ".",
                       std::string pre = "[", std::string suf = "]",
                       bool sp = true)
            : os(o), width(w), fill_char(std::move(fc)),
              empty_char(std::move(ec)), prefix(std::move(pre)),
              suffix(std::move(suf)), show_percent(sp) {}
    };

    template <class Iter>
    class Progress
    {
    public:
        class iterator
        {
            const ProgressConfig *config_;
            size_t current_;
            size_t total_;
            Iter it_;

            void draw() const
            {
                if (!config_)
                    return;
                int percent = current_ * 100 / total_;
                int filled = percent * config_->width / 100;
                config_->os << '\r' << config_->prefix;
                for (int i = 0; i < filled; ++i)
                    config_->os << config_->fill_char;
                for (int i = filled; i < config_->width; ++i)
                    config_->os << config_->empty_char;
                config_->os << config_->suffix;
                if (config_->show_percent)
                {
                    config_->os.width(4);
                    config_->os << percent << '%';
                }
                config_->os.flush();
            }

        public:
            iterator(const ProgressConfig *config, size_t current,
                     size_t total, Iter it)
                : config_(config), current_(current),
                  total_(total), it_(it) {}
            iterator &operator++()
            {
                if (current_ < total_)
                {
                    ++current_;
                    draw();
                }
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            bool operator==(const iterator &other) const
            {
                return current_ == other.current_;
            }
            bool operator!=(const iterator &other) const
            {
                return current_ != other.current_;
            }
            decltype(*it_) operator*() const
            {
                return *it_;
            }
        };

        template <typename Cont>
        Progress(const Cont &cont, const ProgressConfig &config = {})
            : config_(config),
              total_(std::distance(std::begin(cont), std::end(cont))),
              begin_(std::begin(cont)),
              end_(std::end(cont)) {}

        template <typename Cont>
        Progress(Cont &cont, const ProgressConfig &config = {})
            : config_(config),
              total_(std::distance(std::begin(cont), std::end(cont))),
              begin_(std::begin(cont)),
              end_(std::end(cont)) {}

        ~Progress()
        {
            config_.os << std::endl;
        }

        iterator begin()
        {
            return iterator(&config_, 0, total_, begin_);
        }

        iterator end()
        {
            return iterator(&config_, total_, total_, begin_);
        }

    private:
        ProgressConfig config_;
        size_t total_;
        Iter begin_;
        Iter end_;
    };

    namespace ProgressStyle
    {
        inline const ProgressConfig &normal()
        {
            static ProgressConfig cfg{};
            return cfg;
        }

        inline const ProgressConfig &simple()
        {
            static ProgressConfig cfg{std::cout, 50, "=", "-", "", "", false};
            return cfg;
        }

        inline const ProgressConfig &beautiful()
        {
            static ProgressConfig cfg{std::cout, 50, "\u2588", "\u2591",
                                      "\u2595", "\u258F", true};
            return cfg;
        }
    }

    template <class Cont>
    auto progress(Cont &&cont, const ProgressConfig &pc = {})
        -> Progress<decltype(std::begin(cont))>
    {
        return {std::forward<Cont>(cont), pc};
    }
}
