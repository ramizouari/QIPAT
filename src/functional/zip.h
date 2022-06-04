//
// Created by ramizouari on 01/12/2021.
//

#ifndef __ZIP_H__
#define __ZIP_H__
#include <utility>
/*
* This is an iterator used for the zip function. It stores each argument's iterator
*/

namespace functional {
    template<typename ...A>
    struct zip_t;

    template<typename A, typename B>
    struct zip_t<A, B> : public std::pair<A, B> {
        using std::pair<A, B>::pair;
        using iterator_type_1 = decltype(std::pair<A, B>::first.begin());
        using iterator_type_2 = decltype(std::pair<A, B>::second.begin());

        struct zip_iterator {
            iterator_type_1 u;
            iterator_type_2 v;

            zip_iterator &operator++() {
                ++u;
                ++v;
                return *this;
            }

            bool operator==(const zip_iterator &O) const = default;

            std::pair<decltype(*u) &, decltype(*v) &> operator*() const {
                return {*u, *v};
            }
        };

        zip_iterator begin() {
            return zip_iterator{this->first.begin(), this->second.begin()};
        }

        zip_iterator end() {
            return zip_iterator{this->first.end(), this->second.end()};
        }
    };

    template<typename A, typename B, typename C>
    struct zip_t<A, B, C> : public std::tuple<A, B, C> {
        using std::tuple<A, B, C>::tuple;
        using iterator_type_1 = decltype(std::pair<A, B>::first.begin());
        using iterator_type_2 = decltype(std::pair<A, B>::second.begin());
        using iterator_type_3 = decltype(std::pair<A, C>::second.begin());

        struct zip_iterator {
            iterator_type_1 u;
            iterator_type_2 v;
            iterator_type_3 w;

            zip_iterator &operator++() {
                ++u;
                ++v;
                ++w;
                return *this;
            }

            bool operator==(const zip_iterator &O) const = default;

            std::tuple<decltype(*u) &, decltype(*v) &, decltype(*w) &> operator*() const {
                return {*u, *v, *w};
            }
        };

        zip_iterator begin() {
            return zip_iterator{std::get<0>(*this).begin(), std::get<1>(*this).begin(), std::get<2>(*this).begin()};
        }

        zip_iterator end() {
            return zip_iterator{std::get<0>(*this).end(), std::get<1>(*this).end(), std::get<2>(*this).end()};
        }
    };


    template<typename ...A>
    struct zip_t : public std::tuple<A...> {
        using std::tuple<A...>::tuple;

        struct zip_iterator {
            std::tuple<decltype(std::begin(std::declval<A &>()))...> U;

            zip_iterator &operator++() {
                std::apply([](auto &...x) { (..., ++x); }, U);
                return *this;
            }

            bool operator==(const zip_iterator &O) const = default;

            std::tuple<decltype(*std::begin(std::declval<A &>()))...> operator*() const {
                return std::apply(
                        [](auto &...x) -> std::tuple<decltype(*std::begin(std::declval<A &>()))...> { return {*x...}; },
                        U);
            }
        };

        zip_iterator begin() {
            return std::apply([](auto &...x) -> zip_iterator {
                zip_iterator R;
                R.U = {x.begin()...};
                return R;
            }, (std::tuple<A...> &) *this);
        }

        zip_iterator end() {
            return std::apply([](auto &...x) -> zip_iterator {
                zip_iterator R;
                R.U = {x.end()...};
                return R;
            }, (std::tuple<A...> &) *this);
        }
    };

/*
* zip is used to iterate over a tuple of iterables having the same size
* All captured values are by r/l-reference.
* @Requirements
* - Each type A is an iterable having a forward iterator.
* - All the iterables have the same size.
*/
    template<typename ...A>
    zip_t<A &&...> zip(A &&... a) {
        zip_t<A &&...> S(std::forward<A>(a)...);
        return S;
    }

/*
* zip is used to iterate over a tuple of iterables having the same size
* All captured values are copies of the original ones.
* @Requirements
* - Each type A is an iterable having a forward iterator
* - All the iterables have the same size
*/
    template<typename ...A>
    zip_t<A...> zip_copy(const A &... a) {
        zip_t<A...> S(a...);
        return S;
    }

    template<typename ...A>
    zip_t<A...> zip_move(const A &&... a) {
        zip_t<A...> S(std::forward<A>(a)...);
        return S;
    }

/*
* zip is used to iterate over a tuple of const iterables having the same size
* All captured values are by r/l-reference.
* @Requirements
* - Each type A is an iterable having a forward iterator
* - All the iterables have the same size
*/
    template<typename ...A>
    zip_t<const A &...> zip_const(const A &... a) {
        zip_t<const A &...> S(a...);
        return S;
    }
}
#endif //ACPC_PREPARATION_ABSTRACT_ALGEBRA_H
