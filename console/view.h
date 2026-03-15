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
        Iterator begin_, end_;

    public:
        typedef Iterator iterator;
        typedef Iterator const_iterator;

        Iterator begin() const { return begin_; }
        Iterator end() const { return end_; }
        Iterator cbegin() const { return begin_; }
        Iterator cend() const { return end_; }

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
