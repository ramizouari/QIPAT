#ifndef __ORDER_H__
#define __ORDER_H__
#include "abstract_algebra.h"
#include <compare>
#include <variant>


namespace algebra {


/*
* Let (S,<=) be a totally ordered set.
* By definition, a closure order of (S,<=) is a totally ordered set (S',<=)
* Where S'=S∪{a,b} where a,b are not members of S
* Furthermore, we define:
* 1. a<=s for all s in S
* 2. s<=b for all s in S
*/
    struct inf_minus_t;

    struct inf_t : public std::monostate {
    };

    constexpr struct inf_plus_t : public inf_t {
        std::strong_ordering operator<=>(const inf_plus_t &) const = default;

        bool operator==(const inf_plus_t &) const = default;

        bool operator==(const inf_minus_t &) const {
            return false;
        }

        std::strong_ordering operator<=>(const inf_minus_t &) const {
            return 1 <=> 0;
        }
    } inf, inf_plus;

    constexpr struct inf_minus_t : public inf_t {
        bool operator==(const inf_plus_t &) const {
            return false;
        }

        std::strong_ordering operator<=>(const inf_plus_t &) const {
            return 0 <=> 1;
        }

        std::strong_ordering operator<=>(const inf_minus_t &) const = default;
    } inf_min;

    constexpr inf_minus_t operator-(const inf_plus_t &) {
        return inf_min;
    }

    constexpr inf_plus_t operator-(const inf_minus_t &) {
        return inf_plus;
    }

    template<typename S>
    using order_closure = std::variant<inf_minus_t, S, inf_plus_t>;
    using extended_real = order_closure<real>;
    using extended_integer = order_closure<integer>;

/*
* Algebraic Operations on an order closure
* Formally, if S has also a group or ring like structure, we can augment the definition of addition, multiplication
* on almost all elements of S'.
* However, S' does not have the algebraic structure of S
*/
    template<typename S>
    order_closure<S> operator-(const order_closure<S> &A) {
        return std::visit([](const auto &B) -> order_closure<S> { return -B; }, A);
    }

    template<typename S>
    order_closure<S> operator+(const order_closure<S> &A, const order_closure<S> &B) {
        if (A.index() == 1 && B.index() != 1)
            return B;
        else if (A.index() != 1 && B.index() == 1)
            return A;
        else if (A.index() == 1 && B.index() == 1)
            return std::get<S>(A) + std::get<S>(B);
        else if (A.index() == B.index())
            return A;
        else return 0;
    }

    template<typename S>
    order_closure<S> operator-(const order_closure<S> &A, const order_closure<S> &B) {
        if (A.index() == 1 && B.index() != 1)
            return -B;
        else if (A.index() != 1 && B.index() == 1)
            return A;
        else if (A.index() == 1 && B.index() == 1)
            return std::get<S>(A) - std::get<S>(B);
        else if (A.index() == B.index())
            return 0;
        else return A;
    }

    template<typename S>
    order_closure<S> operator-(const order_closure<S> &A, const S &k) {
        if (A.index() == 1)
            return std::get<S>(A) - k;
        else return A;
    }

    template<typename S>
    order_closure<S> operator-(const S &k, const order_closure<S> &A) {
        if (A.index() == 1)
            return std::get<S>(A) - k;
        else return -A;
    }

    template<typename S>
    order_closure<S> operator+(const order_closure<S> &A, const S &k) {
        if (A.index() == 1)
            return std::get<S>(A) + k;
        else return A;
    }

    template<typename S>
    order_closure<S> operator+(const S &k, const order_closure<S> &A) {
        return A + k;
    }

    template<typename S>
    order_closure<S> operator*(const order_closure<S> &A, const order_closure<S> &B) {
        if (A.index() == 1 && B.index() != 1) {
            if (std::get<S>(A) == 0)
                return 0;
            else if (std::get<S>(A) > 0)
                return B;
            else return -B;
        } else if (A.index() != 1 && B.index() == 1) {
            if (std::get<S>(B) == 0)
                return 0;
            else if (std::get<S>(B) > 0)
                return A;
            else return -A;
        } else if (A.index() == 1 && B.index() == 1)
            return std::get<S>(A) * std::get<S>(B);
        return A.index() == B.index() ? order_closure<S>(inf) : order_closure<S>(-inf);
    }

    template<typename S>
    order_closure<S> operator*(const order_closure<S> &A, const S &k) {
        if (A.index() == 1)
            return std::get<S>(A) * k;
        else if (k == 0)
            return 0;
        else if (k > 0)
            return A;
        else return -A;
    }

    template<typename S>
    order_closure<S> operator*(const S &k, const order_closure<S> &A) {
        return operator*(A, k);
    }

    template<typename S>
    order_closure<S> operator/(const order_closure<S> &A, const order_closure<S> &B) {
        if (A.index() == 1 && B.index() != 1)
            return 0;
        else if (A.index() != 1 && B.index() == 1) {
            if (std::get<S>(B) >= 0)
                return A;
            else return -A;
        } else if (A.index() == 1 && B.index() == 1)
            return std::get<S>(A) / std::get<S>(B);
        return A.index() == B.index() ? 1 : -1;
    }

    template<typename S>
    order_closure<S> operator/(const order_closure<S> &A, const S &k) {
        if (A.index() == 1)
            return std::get<S>(A) / k;
        else if (k >= 0)
            return A;
        else return -A;
    }

    template<typename S>
    order_closure<S> operator/(const S &k, const order_closure<S> &A) {
        if (A.index() != 1)
            return 0;
        else return k / std::get<S>(A);
    }

    template<typename S>
    order_closure<S> &operator+=(order_closure<S> &A, const order_closure<S> &B) {
        return A = A + B;
    }

    template<typename S>
    order_closure<S> &operator-=(order_closure<S> &A, const order_closure<S> &B) {
        return A = A - B;
    }

    template<typename S>
    order_closure<S> &operator*=(order_closure<S> &A, const order_closure<S> &B) {
        return A = A * B;
    }

    template<typename S>
    order_closure<S> &operator/=(order_closure<S> &A, const order_closure<S> &B) {
        return A = A / B;
    }

    template<typename S>
    order_closure<S> &operator+=(order_closure<S> &A, const S &B) {
        return A = A + B;
    }

    template<typename S>
    order_closure<S> &operator-=(order_closure<S> &A, const S &B) {
        return A = A - B;
    }

    template<typename S>
    order_closure<S> &operator*=(order_closure<S> &A, const S &B) {
        return A = A * B;
    }

    template<typename S>
    order_closure<S> &operator/=(order_closure<S> &A, const S &B) {
        return A = A / B;
    }
}
#endif