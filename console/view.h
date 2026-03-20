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
#include <cstddef>
#include <iterator>
#include <string>
#include <vector>
#include "csexc.h"

namespace console
{
    template <class Container>
    class View
    {
        using Iterator = typename Container::iterator;
        using cIterator = typename Container::const_iterator;
        Iterator begin_, end_;

    public:
        typedef Iterator iterator;
        typedef cIterator const_iterator;

        Iterator begin() const { return begin_; }
        Iterator end() const { return end_; }
        cIterator cbegin() const { return begin_; }
        cIterator cend() const { return end_; }

        View(Container &container)
            : begin_(std::begin(container)), end_(std::end(container)) {}
        View(Container &container, size_t start_pos, size_t end_pos)
            : begin_(std::next(std::begin(container), start_pos)),
              end_(std::next(std::begin(container), end_pos)) {}
        View(Iterator begin, Iterator end) : begin_(begin), end_(end) {}

        size_t size() const
        {
            return std::distance(begin_, end_);
        }

        auto operator[](size_t pos) const -> decltype(*begin_)
        {
            return *std::next(begin_, pos);
        }

        auto at(size_t pos) const -> decltype(*begin_)
        {
            if (pos >= size())
                throw index_error(std::to_string(pos) +
                                  " out of 0 ~ " +
                                  std::to_string(size() - 1));
            return (*this)[pos];
        }

        Container collect() { return Container(begin_, end_); }
    };

    template <class Container>
    class View<const Container>
    {
        using cIterator = typename Container::const_iterator;
        cIterator begin_, end_;

    public:
        typedef cIterator iterator;
        typedef cIterator const_iterator;

        cIterator begin() const { return begin_; }
        cIterator end() const { return end_; }
        cIterator cbegin() const { return begin_; }
        cIterator cend() const { return end_; }

        View(const Container &container)
            : begin_(std::begin(container)), end_(std::end(container)) {}
        View(const Container &container,
             size_t start_pos, size_t end_pos)
            : begin_(std::next(std::begin(container), start_pos)),
              end_(std::next(std::begin(container), end_pos)) {}
        View(cIterator begin, cIterator end) : begin_(begin), end_(end) {}

        size_t size() const
        {
            return std::distance(begin_, end_);
        }

        auto operator[](size_t pos) const -> decltype(*begin_)
        {
            return *std::next(begin_, pos);
        }

        auto at(size_t pos) const -> decltype(*begin_)
        {
            if (pos >= size())
                throw index_error(std::to_string(pos) +
                                  " out of 0 ~ " +
                                  std::to_string(size() - 1));
            return (*this)[pos];
        }

        Container collect() { return Container(begin_, end_); }
    };

    std::ostream &operator<<(std::ostream &os, const View<std::string> &sv)
    {
        for (auto it = sv.begin(); it != sv.end(); ++it)
        {
            os << *it;
        }
        return os;
    }

    template <class T>
    std::ostream &operator<<(std::ostream &os, const View<T> &v)
    {
        return os << v.collect();
    }
}
