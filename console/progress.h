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

    class Progress
    {
    public:
        struct Config
        {
            std::ostream &os = std::cout;
            int width = 50;
            std::string fill_char = "#";
            std::string empty_char = ".";
            std::string prefix = "[";
            std::string suffix = "]";
            bool show_percent = true;
        };

        class iterator
        {
            const Config *config_;
            size_t current_;
            size_t total_;

            void draw() const
            {
                if (!config_)
                    return;
                int percent = current_ * 100.0 / total_;
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
            iterator(const Config *config, size_t current, size_t total)
                : config_(config), current_(current), total_(total) {}
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
            size_t operator*() const
            {
                return current_;
            }
        };

        template <typename Cont>
        Progress(const Cont &cont, const Config &config = normal())
            : config_(config),
              total_(std::distance(std::begin(cont), std::end(cont))) {}

        ~Progress()
        {
            config_.os << std::endl;
        }

        iterator begin()
        {
            return iterator(&config_, 0, total_);
        }

        iterator end()
        {
            return iterator(&config_, total_, total_);
        }

        static const Config &normal()
        {
            static Config cfg{};
            return cfg;
        }

        static const Config &simple()
        {
            static Config cfg{std::cout, 50, "=", "-", "", "", false};
            return cfg;
        }

        static const Config &beautiful()
        {
            static Config cfg{std::cout, 50, "\u2588", "\u2591",
                              "\u2595", "\u258F",
                              true};
            return cfg;
        }

    private:
        Config config_;
        size_t total_;
    };
}
