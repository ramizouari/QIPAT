//
// Created by ramizouari on 01/12/2021.
//
#ifndef __RING__EXTENSION__
#define __RING__EXTENSION__
#include "algebra/abstract_algebra.h"
#include "polynomial.h"
namespace poly {

    using namespace algebra;

/*
 * This header contains a list of usual ring extensions:
 * 1. field of fractions for an integral ring R
 * 2. nilpotent extension of a ring R: formally it is isomorphic to R[x]/x^k where k is the nilpotence index
 * 3. idempotent extention of a ring R: formally it is isomorphic to R[x]/(x^k-x^(k-1)) where k is the idempotence index
 * 4. ring extension of a ring R with a polynomial q: formally it is isomorphic to R[x]/q(x)
 * 5. quadratic extension of a ring R with a polynomial x²-ax-b: formally it is isomorphic to R[x]/(x²-ax-b) 
 */

    template<typename R>
    struct rational_t {
        R p;
        R q;
    };

/**
* @brief Rational Extension
* @details This is the field of fractions over R.
* @Requirements
* <ol>
 * <li>R is an integral domain. In particular, R should be an euclidean domain</li>
* <li>  R is not a field</li>
 * </ol>
* @Notes
* We excluded the case R is a field, because
* <ol>
 * <li> Otherwise, Frac(R) will be isomorphic to R</li>
* <li> Euclidean division is frequently not implemented when R is a field</li>
 * </ol>
*/
    template<typename R>
    class rational_extension {
        R p, q;

        void reduce() {
            auto d = gcd(p, q);
            p /= d;
            q /= d;
        }

    public:
        /**
        * Initialize a rational element
        * @Requirements
        * <strong>q</strong> is not zero
        */
        rational_extension(R _p = 0, R _q = 1) : p(_p), q(_q) {
            reduce();
        }

        bool operator==(const rational_extension &O) const {
            return p * O.q == O.p * q;
        }

        bool operator!=(const rational_extension &O) const {
            return p * O.q != O.p * q;
        }

        bool operator==(R a) const {
            return p == a * q;
        }

        bool operator!=(R a) const {
            return p != a * q;
        }

        auto &operator+=(const rational_extension &o) {
            p = p * o.q + o.p * q;
            q *= o.q;
            reduce();
            return *this;
        }

        auto &operator-=(const rational_extension &o) {
            p = p * o.q - o.p * q;
            q *= o.q;
            reduce();
            return *this;
        }

        auto &operator*=(const rational_extension &o) {
            p *= o.p;
            q *= o.q;
            reduce();
            return *this;
        }

        auto operator+(const rational_extension &o) const {
            auto r = *this;
            return r += o;
        }

        auto operator-(const rational_extension &o) const {
            auto r = *this;
            return r -= o;
        }

        auto operator*(const rational_extension &o) const {
            auto r = *this;
            return r *= o;
        }

        auto inv() const {
            return rational_extension(q, p);
        }

        auto &operator/=(const rational_extension &O) {
            return *this *= O.inv();
        }

        auto operator/(const rational_extension &O) const {
            auto r = *this;
            return r /= O;
        }

        auto operator-() const {
            return rational_extension(-p, q);
        }

        operator rational_t<R>() const {
            return rational_t<R>{p, q};
        }

        template<size_t k>
        auto &get() &{
            if constexpr (k == 0)
                return p;
            else return q;
        }

        template<size_t k>
        const auto &get() const &{
            if constexpr (k == 0)
                return p;
            else return q;
        }

        template<size_t k>
        auto &&get() const &&{
            if constexpr (k == 0)
                return p;
            else return q;
        }

        template<size_t k>
        auto &&get() &&{
            if constexpr (k == 0)
                return p;
            else return q;
        }
    };


/**
* Extension of R into R[x]/x^n. with n the nilpotence index
* @Requirements:
* <strong>R</strong> is a commutative ring
*/
template<typename R, int nilpotence>
class nilpotent_extension {
    std::vector<R> p;

    void reduce() {
        while (!p.empty() && p.back() == 0)
            p.pop_back();
    }

public:
    nilpotent_extension(R k = 0) : p(1, k) {
        reduce();
    }

    nilpotent_extension(const std::vector<R> &_p) {
        int n = _p.size();
        p.resize(std::min(n, nilpotence));
        for (int i = 0; i < std::min(n, nilpotence); i++)
            p[i] = _p[i];
        reduce();
    }

    auto &operator+=(const nilpotent_extension &O) {
        p.resize(std::max(p.size()), O.p.size());
        for (int i = 0; i < O.size(); i++)
            p[i] += O.p[i];
        reduce();
        return *this;
    }

    auto &operator-=(const nilpotent_extension &O) {
        p.resize(std::max(p.size()), O.p.size());
        for (int i = 0; i < O.size(); i++)
            p[i] -= O.p[i];
        reduce();
        return *this;
    }

    nilpotent_extension operator*(const nilpotent_extension &O) const {
        if (p.empty() || O.p.empty())
            return 0;
        nilpotent_extension q;
        int n = p.size() - 1, m = O.p.size() - 1;
        q.p.resize(std::min(n + m + 1, nilpotence));
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m && (i + j) < nilpotence; j++)
                q.p[i + j] += p[i] * O.p[j];
        q.reduce();
        return q;
    }

    auto &operator*=(const nilpotent_extension &O) {
        auto q = (*this) * O;
        p.swap(q.p);
        return *this;
    }

    auto operator+(const nilpotent_extension &O) const {
        auto q = *this;
        return q += O;
    }

    auto operator-(const nilpotent_extension &O) const {
        auto q = *this;
        return q -= O;
    }

    auto &operator[](int k) {
        return p[k];
    }

    const auto &operator[](int k) const {
        return p[k];
    }

    auto begin() {
        return p.begin();
    }

    auto end() {
        return p.end();
    }

    auto begin() const {
        return p.begin();
    }

    auto end() const {
        return p.end();
    }
};

struct nilpotence_t {
    int n;
};

/**
* This is simply the union of R[x]/x^n over all n
* @Requirements
* <strong> R </strong> is a commutative ring
* @Notes
* If we don't specify the index manually. It will be equal as default to the public static member nilpotence
* @Warning
* the value of nilpotence should be initialized.
*/
template<typename R>
class d_nilpotent_extension {
    std::vector<R> p;
    int index;

    void reduce() {
        while (!p.empty() && (p.back() == 0 || p.size() > index))
            p.pop_back();
    }

public:
    inline static int nilpotence;

    d_nilpotent_extension(R k = 0, nilpotence_t nil_index = {nilpotence}) : p(1, k), index(nil_index.n) {
        reduce();
    }

    explicit d_nilpotent_extension(nilpotence_t index) : d_nilpotent_extension(0, index) {}

    d_nilpotent_extension(const std::vector<R> &_p, nilpotence_t nil_index = {nilpotence}) : index(nil_index.n) {
        int n = _p.size();
        p.resize(std::min(n, index));
        for (int i = 0; i < std::min(n, index); i++)
            p[i] = _p[i];
        reduce();
    }

    auto &operator+=(const d_nilpotent_extension &O) {
        p.resize(std::max(p.size()), O.p.size());
        for (int i = 0; i < O.size(); i++)
            p[i] += O.p[i];
        reduce();
        return *this;
    }

    auto &operator-=(const d_nilpotent_extension &O) {
        p.resize(std::max(p.size()), O.p.size());
        for (int i = 0; i < O.size(); i++)
            p[i] -= O.p[i];
        reduce();
        return *this;
    }

    d_nilpotent_extension operator*(const d_nilpotent_extension &O) const {
        if (p.empty() || O.p.empty())
            return 0;
        d_nilpotent_extension q(nilpotence_t{index});
        int n = p.size() - 1, m = O.p.size() - 1;
        q.p.resize(std::min(n + m + 1, index));
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m && (i + j) < index; j++)
                q.p[i + j] += p[i] * O.p[j];
        q.reduce();
        return q;
    }

    auto &operator*=(const d_nilpotent_extension &O) {
        auto q = (*this) * O;
        p.swap(q.p);
        return *this;
    }

    auto operator+(const d_nilpotent_extension &O) const {
        auto q = *this;
        return q += O;
    }

    auto operator-(const d_nilpotent_extension &O) const {
        auto q = *this;
        return q -= O;
    }

    auto &operator[](int k) {
        return p[k];
    }

    const auto &operator[](int k) const {
        return p[k];
    }

    auto begin() {
        return p.begin();
    }

    auto end() {
        return p.end();
    }

    auto begin() const {
        return p.begin();
    }

    auto end() const {
        return p.end();
    }

    operator std::vector<R> &() {
        return p;
    }
};

/*
* Extension of R into R[x]/(x^(n+1)-x^n). with n the idempotence index
* @Requirements:
* None
*/
template<typename R, int idempotence>
class idempotent_extension {
    std::vector<R> p;

    void reduce() {
        while (!p.empty() && p.back() == 0)
            p.pop_back();
    }

public:
    idempotent_extension(R k = 0) : p(1, k) {
        reduce();
    }

    idempotent_extension(const std::vector<R> &_p) {
        int n = _p.size();
        p.resize(std::min(n, idempotence));
        for (int i = 0; i < n; i++)
            p[i] = _p[std::min(i, idempotence - 1)];
        reduce();
    }

    auto &operator+=(const idempotent_extension &O) {
        p.resize(std::max(p.size()), O.p.size());
        for (int i = 0; i < O.size(); i++)
            p[i] += O.p[i];
        reduce();
        return *this;
    }

    auto &operator-=(const idempotent_extension &O) {
        p.resize(std::max(p.size()), O.p.size());
        for (int i = 0; i < O.size(); i++)
            p[i] -= O.p[i];
        reduce();
        return *this;
    }

    idempotent_extension operator*(const idempotent_extension &O) const {
        if (p.empty() || O.p.empty())
            return 0;
        idempotent_extension q;
        int n = p.size() - 1, m = O.p.size() - 1;
        q.p.resize(std::min(n + m + 1, idempotence));
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                q.p[std::min(i + j, idempotence - 1)] += p[i] * O.p[j];
        q.reduce();
        return q;
    }

    auto &operator*=(const idempotent_extension &O) {
        auto q = (*this) * O;
        p.swap(q.p);
        return *this;
    }

    auto operator+(const idempotent_extension &O) const {
        auto q = *this;
        return q += O;
    }

    auto operator-(const idempotent_extension &O) const {
        auto q = *this;
        return q -= O;
    }

    auto begin() {
        return p.begin();
    }

    auto end() {
        return p.end();
    }

    auto begin() const {
        return p.begin();
    }

    auto end() const {
        return p.end();
    }

    auto &operator[](int k) {
        return p[k];
    }

    const auto &operator[](int k) const {
        return p[k];
    }
};

/**
 * Extension of the ring R to R[x]/q(x) where q is a given poylnomial
 * @Requirements
 * One of the following:
 *  - R is a commutative ring and q is a monic polynomial
 *  - R is a field and q is not zero
 * @Warning
 * the value of q should be initialized.
 */
template<typename R>
class ring_extension {
    polynomial <R> p;
public:
    void reduce() {
        if (p.degree() >= q.degree())
            p = p % q;
        p.reduce();
    }

    inline static polynomial <R> q;

    ring_extension(R k = 0) : p(k) {
        reduce();
    }

    ring_extension(const std::vector<R> &_p) : p(_p) {
        reduce();
    }

    auto &operator+=(const ring_extension &O) {
        p += O.p;
        return *this;
    }

    auto &operator-=(const ring_extension &O) {
        p -= O.p();
        return *this;
    }

    auto operator*(const ring_extension &O) const {
        auto q = *this;
        return q *= O;
    }

    auto &operator*=(const ring_extension &O) {
        p *= O.p;
        reduce();
        return *this;
    }

    auto operator+(const ring_extension &O) const {
        auto q = *this;
        return q += O;
    }

    auto operator-(const ring_extension &O) const {
        auto q = *this;
        return q -= O;
    }

    /*
     * Calculates the multiplicative inverse of an element p
     * @Requirements
     * 1. d=gcd(p,q) is a non-zero constant polynomial
     * 2. One of the following:
     *  2.1 R is a commutative ring and d is invertible 
     *  2.2 R is an euclidean domain and d | a
     * @Notes
     * For (2.2),The divisibility relation is defined as:
     * d | a iff d | s for all s in a
     */
    auto inv() const {
        auto [a, b, d] = egcd(p, q);
        return a / d[0];
    }

    /*
     * Calculates a multiplicative pseudo-inverse of an element p
     * @Requirements
     * None
     */
    auto pinv() const {
        return egcd(p, q).a;
    }

    auto &operator/=(const ring_extension &O) {
        return (*this) *= O.inv();
    }

    auto operator/(const ring_extension &O) const {
        return (*this) * O.inv();
    }

    auto &operator/=(R k) {
        for (auto &s: p)
            s /= k;
        return *this;
    }

    auto &operator*=(R k) {
        for (auto &s: p)
            s *= k;
        return *this;
    }

    auto operator/(R k) const {
        auto q = *this;
        return q /= k;
    }

    auto operator*(R k) const {
        auto q = *this;
        return q *= k;
    }

    auto begin() {
        return p.begin();
    }

    auto end() {
        return p.end();
    }

    auto begin() const {
        return p.begin();
    }

    auto end() const {
        return p.end();
    }

    auto &operator[](int k) {
        return p[k];
    }

    const auto &operator[](int k) const {
        return p[k];
    }
};


/*
 * Extension of the commutative ring R into R[x]/(x²-ax-b)
 * @Requirements:
 * None
 * */
template<typename R, integer a, integer b>
class quadratic_extension {
    std::array<R, 2> p;
public:

    quadratic_extension(R k = 0, R s = 0) : p({k, s}) {
    }

    quadratic_extension(const std::array<R, 2> &_p) : p(_p) {
    }

    auto conj() const {
        return quadratic_extension(p[0] + a * p[1], -p[1]);
    }

    auto &operator+=(const quadratic_extension &O) {
        p[0] += O.p[0];
        p[1] += O.p[1];
        return *this;
    }

    auto &operator-=(const quadratic_extension &O) {
        p[0] -= O.p[0];
        p[1] -= O.p[1];
        return *this;
    }

    auto operator*(const quadratic_extension &O) const {
        quadratic_extension q;
        auto s = p[1] * O.p[1];
        q.p[0] = p[0] * O.p[0] + R(b) * s;
        q.p[1] = p[0] * O.p[1] + p[1] * O.p[0] + R(a) * s;
        return q;
    }

    auto &operator*=(const quadratic_extension &O) {
        p = ((*this) * O).p;
        return *this;
    }

    auto operator+(const quadratic_extension &O) const {
        auto q = *this;
        return q += O;
    }

    auto operator-(const quadratic_extension &O) const {
        auto q = *this;
        return q -= O;
    }


    /*
     * Calculate the multiplicative inverse of p
     * @Requirements:
     * One of the following:
     * - p0²+a*p0*p1-b*p1² is inversible
     * - R is an euclidean domain and p0²+a*p0*p1-b*p1² | conj(p)
     * @Notes
     * For (2.2),The divisibility relation is defined as:
     * d | a iff d | s for all s in a
     * */
    auto inv() const {
        return conj() / (p[0] * p[0] + R(a) * p[0] * p[1] - R(b) * p[1] * p[1]);
    }

    /*
     * Divides p by q
     * @Requirements:
     * One of the following:
     * - p0²+a*p0*p1-b*p1² is inversible
     * - R is an euclidean domain and p0²+a*p0*p1-b*p1² | p*conj(q)
     * @Notes
     * 1. Guaranteed to work in an integral domain even if the element O is not inversible,
     * but there still exists Q such that P=Q*O => P/O=Q
     * 2. The divisibility relation is defined as: d | a iff d | s for all s in a
     * */
    auto &operator/=(const quadratic_extension &q) {
        *this *= q.conj();
        return *this /= p[0] * p[0] + R(a) * p[0] * p[1] - R(b) * p[1] * p[1];
    }

    /*
     * Divides p by q and store it to p itself
     * @Requirements:
     * One of the following:
     * - p0²+a*p0*p1-b*p1² is inversible
     * - R is an euclidean domain and p0²+a*p0*p1-b*p1² | p*conj(q)
     * @Notes
     * 1. Guaranteed to work in an integral domain even if the element O is not inversible,
     * but there still exists Q such that P=Q*O => P/O=Q
     * 2. The divisibility relation is defined as: d | a iff d | s for all s in a
     * */
    auto operator/(const quadratic_extension &O) const {
        return ((*this) * O.conj()) / (O.p[0] * O.p[0] + R(a) * O.p[0] * O.p[1] - R(b) * O.p[1] * O.p[1]);
    }

    /*
     * Divides p by k and store it to p itself
     * @Requirements:
     * One of the following:
     * - k is inversible
     * - R is an euclidean domain and k | p
     * @Notes
     * The divisibility relation is defined as: d | a iff d | s for all s in a
     * */
    auto &operator/=(R k) {
        p[0] /= k;
        p[1] /= k;
        return *this;
    }

    auto &operator*=(R k) {
        p[0] *= k;
        p[1] *= k;
        return *this;
    }

    auto &operator-=(R k) {
        p[0] -= k;
        return *this;
    }

    auto &operator+=(R k) {
        p[0] += k;
        return *this;
    }

    auto operator+(R k) const {
        auto q = *this;
        return q += k;
    }

    auto operator-(R k) const {
        auto q = *this;
        return q -= k;
    }

    auto operator/(R k) const {
        auto q = *this;
        return q /= k;
    }

    auto operator*(R k) const {
        auto q = *this;
        return q *= k;
    }

    auto begin() {
        return p.begin();
    }

    auto end() {
        return p.end();
    }

    auto begin() const {
        return p.begin();
    }

    auto end() const {
        return p.end();
    }

    auto &operator[](int k) {
        return p[k];
    }

    const auto &operator[](int k) const {
        return p[k];
    }

    template<size_t k>
    auto &get() &{
        return p[k];
    }

    template<size_t k>
    const auto &get() const &{
        return p[k];
    }

    template<size_t k>
    auto &&get() const &&{
        return p[k];
    }

    template<size_t k>
    auto &&get() &&{
        return p[k];
    }
};

template<typename R, integer a, integer b>
auto operator+(R k, const quadratic_extension<R, a, b> &O) {
    quadratic_extension<R, a, b> q = O;
    return q += k;
}

template<typename R, integer a, integer b>
auto operator*(R k, const quadratic_extension<R, a, b> &O) {
    quadratic_extension<R, a, b> q = O;
    return q *= k;
}

template<typename R, integer a, integer b>
auto operator-(R k, const quadratic_extension<R, a, b> &O) {
    quadratic_extension<R, a, b> q = O;
    return q -= k;
}

/*
 * Dynamic ring extension
 * For a ring R, It is the union of R[x]/q(x) over all polynomials q
 * */

template<typename R>
struct extension_polynomial_t {
    polynomial <R> p;
};

/**
 * @brief Dynamic Ring Extension
 * @details It is simply the union of R[x]/q over all polynomials q
 * @Requirements
 * One of the following:
 *  - R is a commutative ring and q is a monic polynomial
 *  - R is a field and q is not zero
 * @Notes
 * If the polynomial is not specified, its value will be by default that of the public static member extension_polynomial
 * @Warning
 * the value of extension_polynomial should be initialized.
 */
template<typename R>
class d_ring_extension {
    polynomial <R> p;
    polynomial <R> q;
public:
    void reduce() {
        if (p.degree() >= q.degree())
            p = p % q;
        p.reduce();
    }

    inline static polynomial <R> extension_polynomial;

    d_ring_extension(R k = 0, extension_polynomial_t<R> ext = {extension_polynomial}) : p(k), q(ext.p) {
        reduce();
    }

    d_ring_extension(const std::vector<R> &_p, extension_polynomial_t<R> ext = {extension_polynomial}) : p(_p),
                                                                                                         q(ext.p) {
        reduce();
    }

    d_ring_extension(extension_polynomial_t<R> ext) : q(ext.p) {}

    auto &operator+=(const d_ring_extension &O) {
        p += O.p;
        return *this;
    }

    auto &operator-=(const d_ring_extension &O) {
        p -= O.p();
        return *this;
    }

    auto operator*(const d_ring_extension &O) const {
        auto q = *this;
        return q *= O;
    }

    auto &operator*=(const d_ring_extension &O) {
        p *= O.p;
        reduce();
        return *this;
    }

    auto operator+(const d_ring_extension &O) const {
        auto q = *this;
        return q += O;
    }

    auto operator-(const d_ring_extension &O) const {
        auto q = *this;
        return q -= O;
    }

    auto inv() const {
        auto [a, b, d] = egcd(p, q);
        return a / d[0];
    }

    auto pinv() const {
        return egcd(p, q).a;
    }

    auto &operator/=(const d_ring_extension &O) {
        return (*this) *= O.inv();
    }

    auto operator/(const d_ring_extension &O) const {
        return (*this) * O.inv();
    }

    auto begin() {
        return p.begin();
    }

    auto end() {
        return p.end();
    }

    auto begin() const {
        return p.begin();
    }

    auto end() const {
        return p.end();
    }

    auto &operator[](int k) {
        return p[k];
    }

    const auto &operator[](int k) const {
        return p[k];
    }
};

}

namespace std {
    template<typename R>
    struct tuple_size<poly::rational_extension < R>> : integral_constant<size_t, 2> {
};
    template<size_t k, typename R>
    struct tuple_element<k, poly::rational_extension<R>> {
    using type = R;
    };

    template<typename R, int a, int b>
    struct tuple_size<poly::quadratic_extension < R, a, b>> : integral_constant<size_t, 2> {
    };
    template<size_t k, typename R, int a, int b>
    struct tuple_element<k, poly::quadratic_extension<R, a, b>> {
    using type = R;
    };
}


#endif