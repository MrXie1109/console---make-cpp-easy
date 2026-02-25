#pragma once
#include <iterator>
#include <string>
#include <vector>
#include "csexc.h"

namespace console
{
    using namespace std;

    template <class Container>
    class View
    {
        using Iterator = typename Container::iterator;
        Iterator begin_, end_;

    public:
        typedef Iterator iterator;

        Iterator begin() const { return begin_; }
        Iterator end() const { return end_; }

        View(Container &container)
            : begin_(std::begin(container)), end_(std::end(container)) {}
        View(Container &container, size_t start_pos, size_t end_pos)
            : begin_(next(std::begin(container), start_pos)),
              end_(next(std::begin(container), end_pos)) {}
        View(Iterator begin, Iterator end) : begin_(begin), end_(end) {}

        size_t size() const
        {
            return distance(begin_, end_);
        }

        auto operator[](size_t pos) const -> decltype(*begin_)
        {
            return *next(begin_, pos);
        }

        auto at(size_t pos) const -> decltype(*begin_)
        {
            if (pos >= size())
                throw index_error(to_string(pos) +
                                  " out of 0 ~ " +
                                  to_string(size() - 1));
            return (*this)[pos];
        }

        Container collect() { return Container(begin_, end_); }
    };

    template <class Container>
    class ConstView
    {
        using cIterator = typename Container::const_iterator;
        cIterator begin_, end_;

    public:
        typedef cIterator const_iterator;

        cIterator cbegin() const { return begin_; }
        cIterator cend() const { return end_; }

        ConstView(const Container &container)
            : begin_(std::begin(container)), end_(end(container)) {}
        ConstView(const Container &container, size_t start_pos, size_t end_pos)
            : begin_(next(std::begin(container), start_pos)),
              end_(next(std::begin(container), end_pos)) {}
        ConstView(cIterator begin, cIterator end) : begin_(begin), end_(end) {}

        size_t size() const
        {
            return distance(begin_, end_);
        }

        auto operator[](size_t pos) const -> decltype(*begin_)
        {
            return *next(begin_, pos);
        }

        auto at(size_t pos) const -> decltype(*begin_)
        {
            if (pos >= size())
                throw index_error(to_string(pos) +
                                  " out of 0 ~ " +
                                  to_string(size() - 1));
            return (*this)[pos];
        }

        Container collect() { return Container(begin_, end_); }
    };

    ostream &operator<<(ostream &os, const View<string> &sv)
    {
        for (auto it = sv.begin(); it != sv.end(); ++it)
        {
            os << *it;
        }
        return os;
    }

    template <class T>
    ostream &operator<<(ostream &os, const View<T> &v)
    {
        return os << v.collect();
    }
}