//
// Created by ASUS on 30/11/2021.
//
#ifndef __MODULAR__ARITHMETIC__
#define __MODULAR__ARITHMETIC__
#include <cstdint>
#include <utility>
#include "algebra/abstract_algebra.h"
#include <random>
#include <unordered_map>
#include "number_theory.h"
#include "polynomial/ring_extension.h"


namespace nt {
    using namespace algebra;

    template<integer mod>
    class cyclic {
        integer n;
    public:
        inline static bool assume_prime = true;
        inline static constexpr integer m = mod;

        cyclic(int o = 0) : n((o + m) % m) {}

        bool operator==(int O) const {
            return n == (m + O) % m;
        }

        bool operator!=(int O) const {
            return n != (m + O) % m;
        }

        bool operator==(cyclic O) const {
            return n == O.n;
        }

        bool operator!=(cyclic O) const {
            return n != O.n;
        }

        cyclic operator-() const {
            return cyclic(-n);
        }

        auto &operator+=(const cyclic &O) {
            n = (n + O.n) % m;
            return *this;
        }

        auto &operator-=(const cyclic &O) {
            n = (n + m - O.n) % m;
            return *this;
        }

        auto &operator*=(const cyclic &O) {
            n = (n * O.n) % m;
            return *this;
        }

        auto &operator/=(const cyclic &O) {
            return (*this) *= O.inv();
        }

        auto operator*(const cyclic &O) const {
            auto w = *this;
            return w *= O;
        }

        auto operator+(const cyclic &O) const {
            auto w = *this;
            return w += O;
        }

        auto operator-(const cyclic &O) const {
            auto w = *this;
            return w -= O;
        }

        auto operator/(const cyclic &O) const {
            return (*this) * O.inv();
        }

        cyclic pinv() const {
            return egcd(n, m).a;
        }

        auto inv() const {
            if (assume_prime)
                return pow(*this, m - 2);
            else return pinv();
        }

        auto &operator++() {
            return *this += 1;
        }

        auto &operator--() {
            return *this -= 1;
        }

        auto operator++(int) {
            cyclic r(n);
            *this += 1;
            return r;
        }

        auto operator--(int) {
            cyclic r(n);
            *this -= 1;
            return r;
        }

        explicit operator integer &() {
            return n;
        }

        explicit operator const integer &() const {
            return n;
        }
    };

    template<integer m>
    auto operator*(int k, cyclic<m> s) {
        return s * k;
    }

    template<integer m>
    auto operator+(int k, cyclic<m> s) {
        return s + k;
    }

    class d_cyclic {
        integer n;
    public:
        inline static integer m = 1;
        inline static bool assume_prime = true;

        d_cyclic(int o = 0) : n((o + m) % m) {}

        bool operator==(int O) const {
            return n == (m + O) % m;
        }

        bool operator!=(int O) const {
            return n != (m + O) % m;
        }

        bool operator==(d_cyclic O) const {
            return n == O.n;
        }

        bool operator!=(d_cyclic O) const {
            return n != O.n;
        }

        auto &operator+=(const d_cyclic &O) {
            n = (n + O.n) % m;
            return *this;
        }

        auto &operator-=(const d_cyclic &O) {
            n = (n + m - O.n) % m;
            return *this;
        }

        auto &operator*=(const d_cyclic &O) {
            n = (n * O.n) % m;
            return *this;
        }

        auto inv() const {
            if (assume_prime)
                return pow(*this, m - 2);
            else return pinv();
        }

        auto &operator/=(const d_cyclic &O) {
            return (*this) *= O.inv();
        }

        auto operator*(const d_cyclic &O) const {
            auto w = *this;
            return w *= O;
        }

        auto operator+(const d_cyclic &O) const {
            auto w = *this;
            return w += O;
        }

        d_cyclic operator-() const {
            return d_cyclic(m - n);
        }

        auto operator-(const d_cyclic &O) const {
            auto w = *this;
            return w -= O;
        }

        auto operator/(const d_cyclic &O) const {
            return (*this) * O.inv();
        }

        d_cyclic pinv() const {
            return egcd(n, m).a;
        }

        auto &operator++() {
            return *this += 1;
        }

        auto &operator--() {
            return *this -= 1;
        }

        auto operator++(int) {
            d_cyclic r(n);
            *this += 1;
            return r;
        }

        auto operator--(int) {
            d_cyclic r(n);
            *this -= 1;
            return r;
        }

        explicit operator integer &() {
            return n;
        }

        explicit operator const integer &() const {
            return n;
        }
    };

    inline auto operator*(int k, d_cyclic O) {
        return O *= k;
    }


    template<typename cyclic_ring>
    integer discrete_log(cyclic_ring a, cyclic_ring r) {
        integer s = std::ceil(std::sqrt(cyclic_ring::m));
        cyclic_ring u = pow(a, s), w = 1;
        std::unordered_map<cyclic_ring, integer> mapper;
        for (integer i = 0; i <= s; i++, w *= a)
            mapper[r * w] = i;
        w = u;
        for (integer i = 1; i <= s; i++, w *= u)
            if (mapper.count(w))
                return i * s - mapper[w];
        return -1;
    }

    inline std::vector<integer> inverse_table(int n, int prime) {
        std::vector<integer> I(n + 1);
        I[0] = I[1] = 1;
        for (int i = 2; i <= n; i++)
            I[i] = I[prime % i] *
                   (prime - prime / i) % prime;
        return I;
    }

    inline integer primitive_root_of_unity(integer p, factoriser &F) {
        d_cyclic::m = p;
        auto phi = F.totient(p);
        auto D = F.divisors_list(phi);
        for (integer k = 2; k < p - 1; k++) {
            bool is_primitive = true;
            for (auto d: D)
                if (d < phi && pow<d_cyclic>(k, d) == 1) {
                    is_primitive = false;
                    break;
                }
            if (is_primitive)
                return k;
        }
        return 0;
    }

    template<integer p>
    integer primitive_root_of_unity(factoriser &F) {
        static auto phi = F.totient(p);
        static auto D = F.divisors_list(phi);
        for (integer k = 2; k < p - 1; k++) {
            bool is_primitive = true;
            for (auto d: D)
                if (d < phi && pow<d_cyclic>(k, d) == 1) {
                    is_primitive = false;
                    break;
                }
            if (is_primitive)
                return k;
        }
        return 0;
    }

    template<typename cyclic_field>
    integer legendre_symbol(cyclic_field a) {
        integer r = (integer) pow(a, (cyclic_field::m - 1) / 2);
        if (r > cyclic_field::m / 2)
            r -= cyclic_field::m;
        return r;
    }

    template<typename cyclic_field>
    cyclic_field sqrt(cyclic_field n) {
        if (cyclic_field::m == 2)
            return n;
        cyclic_field a = 2;
        while (legendre_symbol(a * a - n) != -1)
            ++a;
        poly::extension_polynomial_t q = {poly::polynomial<cyclic_field>({n - a * a, 0, 1})};
        poly::d_ring_extension<cyclic_field> phi(std::vector<cyclic_field>{a, 1}, q);
        return pow(phi, (cyclic_field::m + 1) / 2, q)[0];
    }
}



template<>
struct std::hash<nt::d_cyclic> {
    inline static std::random_device dev = std::random_device();
    inline static std::mt19937 g = std::mt19937(dev());
    inline static constexpr nt::integer M = 1e9 + 7;
    std::uniform_int_distribution<nt::integer> d = std::uniform_int_distribution<nt::integer>(1, M);
    nt::integer a = d(g), b = d(g);
public:
    auto operator()(const nt::d_cyclic &x) const {
        return (a * static_cast<nt::integer>(x) + b) % M;
    }
};

template<nt::integer m>
struct std::hash<nt::cyclic<m>> {
inline static std::random_device dev = std::random_device();
inline static std::mt19937 g = std::mt19937(dev());
inline static constexpr nt::integer M = 1e9 + 7;
std::uniform_int_distribution<nt::integer> d = std::uniform_int_distribution<nt::integer>(1, M);
nt::integer a = d(g), b = d(g);
public:
size_t operator()(const nt::cyclic<m> &x) const noexcept {
    return (a * static_cast<nt::integer>(x) + b) % M;
}
};
#endif