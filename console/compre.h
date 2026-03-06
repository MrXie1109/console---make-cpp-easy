#pragma once
#include <list>
#include <utility>
#include <iterator>

namespace console
{
    using namespace std;

    template <class T>
    class Compre
    {
    protected:
        vector<T> vec;

    public:
        Compre() : vec() {}

        template <class Cont>
        Compre(const Cont &cont) : vec(begin(cont), end(cont)) {}

        template <class Cont>
        Compre(Cont &&cont) : vec(
                                  make_move_iterator(begin(cont)),
                                  make_move_iterator(end(cont))) {}

        template <class Cont>
        Compre(const Cont &cont, size_t start_pos, size_t end_pos)
            : vec(next(begin(cont), start_pos),
                  next(begin(cont), end_pos)) {}

        template <class Cont>
        Compre(Cont &&cont, size_t start_pos, size_t end_pos)
            : vec(make_move_iterator(next(begin(cont), start_pos)),
                  make_move_iterator(next(begin(cont), end_pos))) {}

        template <class Iter>
        Compre(Iter beg, Iter end) : vec(beg, end) {}

        Compre(initializer_list<T> init) : vec(init) {}

        template <class F>
        auto map(F &&f) const -> Compre<decltype(f(vec[0]))>
        {
            Compre<decltype(f(vec[0]))> tmp;
            for (const T &item : vec)
                tmp.vec.push_back(f(item));
            return tmp;
        }

        template <class F>
        Compre<T> filter(F &&f) const
        {
            Compre<T> tmp;
            for (const T &item : vec)
                if (f(item))
                    tmp.vec.push_back(item);
            return tmp;
        }

        template <class Cont>
        Cont to()
        {
            return Cont(
                make_move_iterator(vec.begin()),
                make_move_iterator(vec.end()));
        }

        template <class Cont>
        Cont make() const
        {
            return Cont(vec.begin(), vec.end());
        }
    };

    template <template <class> class Cont, class T>
    Compre<T> make_compre(const Cont<T> &cont)
    {
        return Compre<T>(cont);
    }

    template <template <class> class Cont, class T>
    Compre<T> make_compre(Cont<T> &&cont)
    {
        return Compre<T>(move(cont));
    }

    template <template <class> class Cont, class T>
    Compre<T> make_compre(const Cont<T> &cont, size_t start_pos, size_t end_pos)
    {
        return Compre<T>(cont, start_pos, end_pos);
    }

    template <template <class> class Cont, class T>
    Compre<T> make_compre(Cont<T> &&cont, size_t start_pos, size_t end_pos)
    {
        return Compre<T>(move(cont), start_pos, end_pos);
    }

    template <class Iter>
    auto make_compre(Iter beg, Iter end) -> Compre<decltype(*beg)>
    {
        return Compre<decltype(*beg)>(beg, end);
    }

    template <class T>
    Compre<T> make_compre(initializer_list<T> init)
    {
        return Compre<T>(init);
    }
}
