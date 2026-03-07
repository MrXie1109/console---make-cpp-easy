#pragma once
#include <vector>
#include <utility>
#include <iterator>

namespace console
{
    template <class T>
    class Comprehension
    {
    protected:
        std::vector<T> vec;

    public:
        Comprehension() : vec() {}

        template <class Cont>
        Comprehension(const Cont &cont)
            : vec(std::begin(cont), std::end(cont)) {}

        template <class Cont>
        Comprehension(Cont &&cont)
            : vec(
                  std::make_move_iterator(std::begin(cont)),
                  std::make_move_iterator(std::end(cont))) {}

        template <class Cont>
        Comprehension(const Cont &cont, size_t start_pos, size_t end_pos)
            : vec(std::next(std::begin(cont), start_pos),
                  std::next(std::begin(cont), end_pos)) {}

        template <class Cont>
        Comprehension(Cont &&cont, size_t start_pos, size_t end_pos)
            : vec(std::make_move_iterator(
                      std::next(std::begin(cont), start_pos)),
                  std::make_move_iterator(
                      std::next(std::begin(cont), end_pos))) {}

        template <class Iter>
        Comprehension(Iter beg, Iter end) : vec(beg, end) {}

        Comprehension(std::initializer_list<T> init) : vec(init) {}

        std::vector<T> &get_vec()
        {
            return vec;
        }

        template <class F>
        auto map(F &&f) const -> Comprehension<decltype(f(vec[0]))>
        {
            Comprehension<decltype(f(vec[0]))> tmp;
            for (const T &item : vec)
                tmp.get_vec().push_back(f(item));
            return tmp;
        }

        template <class F>
        Comprehension<T> filter(F &&f) const
        {
            Comprehension<T> tmp;
            for (const T &item : vec)
                if (f(item))
                    tmp.vec.push_back(item);
            return tmp;
        }

        template <class Cont>
        Cont to()
        {
            return Cont(
                std::make_move_iterator(vec.begin()),
                std::make_move_iterator(vec.end()));
        }

        template <class Cont>
        Cont make() const
        {
            return Cont(vec.begin(), vec.end());
        }
    };

    template <class Cont>
    auto make_compre(const Cont &cont)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(cont);
    }

    template <class Cont>
    auto make_compre(Cont &&cont)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(std::move(cont));
    }

    template <class Cont>
    auto make_compre(const Cont &cont, size_t start_pos, size_t end_pos)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(
            cont, start_pos, end_pos);
    }

    template <class Cont>
    auto make_compre(Cont &&cont, size_t start_pos, size_t end_pos)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(
            std::move(cont), start_pos, end_pos);
    }

    template <class Iter>
    auto make_compre(Iter beg, Iter end) -> Comprehension<decltype(*beg)>
    {
        return Comprehension<decltype(*beg)>(beg, end);
    }

    template <class T>
    Comprehension<T> make_compre(std::initializer_list<T> init)
    {
        return Comprehension<T>(init);
    }
}
