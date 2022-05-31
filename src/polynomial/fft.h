//
// Created by ASUS on 01/12/2021.
//

#ifndef ACPC_PREPARATION_FFT_H
#define ACPC_PREPARATION_FFT_H
#include "algebra/abstract_algebra.h"
#include <numbers>
#include "polynomial.h"
#include "nt/number_theory.h"
#include <algorithm>
#include <optional>
#include <thread>
#include <future>
#include "nt/modular_arithmetic.h"
#include "functional/zip.h"

namespace fft {
    using namespace poly;
    using namespace algebra;
    using nt::factoriser;
    using nt::d_cyclic;
    const real pi = acos(-1);

/*
 * Fast Fourier Transform over Complex numbers
 * Suitable for smooth numbers
 * */
    template<bool is_inverse = false>
    struct fast_fourier {
        int n;
        std::complex<real> w;
        using IC = std::complex<real>;
        inline static constexpr int sign = is_inverse ? 1 : -1;
        inline static std::optional<std::reference_wrapper<factoriser>> F_ref = std::optional<std::reference_wrapper<factoriser>>();

    public:
        inline static bool use_normalized = false;

        fast_fourier(int _n) : n(_n), w(std::exp(IC(0, 2 * sign * pi / n))) {
        }

        virtual std::vector<IC> unnormalized(const std::vector<IC> &X) const {
            if (n == 1)
                return X;
            auto &F = F_ref.value().get();
            auto p = F.smallest_divisor(n), q = n / p;
            fast_fourier<is_inverse> FFT(q);
            std::vector<std::vector<IC>> U(p, std::vector<IC>(q));
            for (int i = 0; i < n; i++)
                U[i % p][i / p] = X[i];
            std::vector<std::vector<IC>> V(p);
            for (int i = 0; i < p; i++)
                V[i] = FFT.unnormalized(U[i]);
            std::vector<IC> R(n);
            IC z = std::pow(w, q);
            IC t = 1;
            for (int i = 0; i < p; i++, t *= z) {
                IC h1 = 1, h2 = 1;
                for (int j = 0; j < p; j++, h1 *= t, h2 *= w) {
                    IC h3 = 1;
                    for (int k = 0; k < q; k++, h3 *= h2)
                        R[i * q + k] += h1 * h3 * V[j][k];
                }
            }
            return R;
        }

        std::vector<IC> operator()(const std::vector<IC> &X) const {
            return use_normalized ? normalized(X) : unnormalized(X);
        }

        std::vector<IC> normalized(const std::vector<IC> &X) const {
            auto Y = unnormalized(X);
            for (auto &y: Y)
                y /= std::sqrt(n);
            return Y;
        }

        static void set_factoriser(factoriser &F) {
            F_ref = F;
            fast_fourier<!is_inverse>::F_ref = F;
        }

        static factoriser &get_factoriser() {
            return F_ref.value();
        }
    };

    struct parallel_implementation
    {
        inline static unsigned int HARD_CONCURRENCY=std::thread::hardware_concurrency();
        inline static unsigned int SOFT_CONCURRENCY=8*HARD_CONCURRENCY;
    };


    template<bool is_inverse = false>
    struct parallel_fast_fourier :public fast_fourier<is_inverse> , protected parallel_implementation {
        using fast_fourier<is_inverse>::n;
        using fast_fourier<is_inverse>::w;
        using fast_fourier<is_inverse>::sign;
        using fast_fourier<is_inverse>::use_normalized;
        using fast_fourier<is_inverse>::F_ref;
        using fast_fourier<is_inverse>::fast_fourier;
        using fast_fourier<is_inverse>::normalized;
        using fast_fourier<is_inverse>::operator();
        using parallel_implementation::HARD_CONCURRENCY;
        using parallel_implementation::SOFT_CONCURRENCY;
        inline static std::atomic<unsigned int> counter=0;

        virtual std::vector<IC> unnormalized(const std::vector<IC> &X) const {
            if(counter > SOFT_CONCURRENCY)
                return fast_fourier<is_inverse>::unnormalized(X);
            if (n == 1)
                return X;
            counter++;
            auto &F = F_ref.value().get();
            auto p = F.smallest_divisor(n), q = n / p;
            fast_fourier<is_inverse> FFT(q);
            std::vector<std::vector<IC>> U(p, std::vector<IC>(q));
            for (int i = 0; i < n; i++)
                U[i % p][i / p] = X[i];
            std::vector<std::vector<IC>> V(p);
            auto L=p/SOFT_CONCURRENCY;
            std::vector<std::future<std::vector<IC>>> futures;
            for(int i=0;i<p;i++)
                futures.emplace_back(std::async(std::launch::async,&fast_fourier<is_inverse>::unnormalized,&FFT,U[i]));
            for(auto [v,f]: functional::zip(V,futures))
                v=f.get();
            std::vector<IC> R(n);
            IC z = std::pow(w, q);
            IC t = 1;
            for (int i = 0; i < p; i++, t *= z) {
                IC h1 = 1, h2 = 1;
                for (int j = 0; j < p; j++, h1 *= t, h2 *= w) {
                    IC h3 = 1;
                    for (int k = 0; k < q; k++, h3 *= h2)
                        R[i * q + k] += h1 * h3 * V[j][k];
                }
            }
            counter--;
            return R;
        }


    };

/*
 * Fast Fourier Transform over Complex numbers
 * Works only on power of two (optimized for this case)
 * */

    template<bool is_inverse = false>
    struct fast_fourier_base_2 : public fast_fourier<is_inverse> {
    public:
        using fast_fourier<is_inverse>::fast_fourier;

        std::vector<IC> unnormalized(const std::vector<IC> &X) const {
            auto &n = this->n;
            auto &w = this->w;
            if (n == 1)
                return X;
            constexpr int p = 2;
            auto q = n / p;
            fast_fourier_base_2<is_inverse> FFT(q);
            std::vector<IC> U1(q), U2(q);
            for (int i = 0; i < n; i += 2) {
                U1[i / p] = X[i];
                U2[i / p] = X[i + 1];
            }
            std::vector<IC> V1 = FFT.unnormalized(U1), V2 = FFT.unnormalized(U2);
            IC s = 1;
            for (int i = 0; i < q; i++, s *= w)
                V2[i] *= s;
            std::vector<IC> R(n);
            for (int i = 0; i < n / p; i++)
                R[i] = V1[i] + V2[i];
            for (int i = 0; i < n / p; i++)
                R[i + n / p] = V1[i] - V2[i];
            return R;
        }
    };

    using inverse_fast_fourier = fast_fourier<true>;
    using inverse_fast_fourier_base_2 = fast_fourier_base_2<true>;

    inline std::vector<IC> fast_multiplication(std::vector<IC> x, std::vector<IC> y, factoriser &F) {
        fast_fourier<>::set_factoriser(F);
        int n = x.size(), m = y.size();
        int r = n + m - 1;
        fast_fourier FFT(r);
        inverse_fast_fourier IFFT(r);
        x.resize(r);
        y.resize(r);
        auto u = FFT(x), v = FFT(y);
        std::vector<IC> w(r);
        for (int i = 0; i < r; i++)
            w[i] = u[i] * v[i];
        auto z = IFFT(w);
        for (auto &s: z)
            s /= r;
        z.resize(n + m - 1);
        return z;
    }

    inline std::vector<IC> fast_multiplication(std::vector<IC> x, std::vector<IC> y) {
        int n = x.size(), m = y.size();
        int r = std::bit_ceil<unsigned int>(n + m - 1);
        x.resize(r);
        y.resize(r);
        fast_fourier_base_2<> FFT(r);
        inverse_fast_fourier_base_2 IFFT(r);
        auto u = FFT(x), v = FFT(y);
        std::vector<IC> w(r);
        for (int i = 0; i < r; i++)
            w[i] = u[i] * v[i];
        auto z = IFFT(w);
        for (auto &s: z)
            s /= r;
        z.resize(n + m - 1);
        return z;
    }

    inline polynomial <IC> fast_multiplication(const polynomial <IC> &x, const polynomial <IC> &y,
                                        factoriser &F = fast_fourier<>::get_factoriser()) {
        return fast_multiplication(static_cast<const std::vector<IC> &>(x),
                                   static_cast<const std::vector<IC> &>(y), F);
    }


    template<typename R>
    struct fast_hadamard {
        int m;
    public:
        fast_hadamard(int _m) : m(_m) {}

        std::vector<R> unnormalized(const std::vector<R> &X) const {
            auto n = 1 << m;
            if (m == 0)
                return X;
            fast_hadamard FHT(m - 1);
            std::vector<R> U1(n >> 1), U2(n >> 1);
            for (int i = 0; i < (n >> 1); i++) {
                U1[i] = X[i];
                U2[i] = X[i + (n >> 1)];
            }
            std::vector<R> V1 = FHT.unnormalized(U1), V2 = FHT.unnormalized(U2);
            std::vector<R> S(n);
            for (int i = 0; i < (n >> 1); i++)
                S[i] = V1[i] + V2[i];
            for (int i = 0; i < (n >> 1); i++)
                S[i + (n >> 1)] = V1[i] - V2[i];
            return S;
        }

        auto operator()(const std::vector<R> &X) const {
            return unnormalized(X);
        }
    };

    template<int n, typename T>
    struct tensor_t {
        using tensor = std::vector<typename tensor_t<n - 1, T>::tensor>;
        std::vector<tensor_t<n - 1, T>> U;

        T operator[](const std::array<T, n> &I) const {
            std::array<T, n - 1> subI = {};
            for (int i = 1; i < n; i++)
                subI[i - 1] = I[i];
            return U[subI];
        }

        explicit operator std::vector<tensor_t<n - 1, T>> &() const {
            return U;
        }
    };

    template<typename T>
    struct tensor_t<0, T> {
        using tensor = T;
        tensor U;

        T operator[](const std::array<T, 0> &) {
            return U;
        }

        operator const T &() const {
            return U;
        }
    };

    template<int n, typename T>
    using tensor = typename tensor_t<n, T>::tensor;

    template<typename T, int n>
    T get(const tensor<n, T> &A, std::array<int, n> I) {
        if constexpr (n == 0)
            return A;
        else {
            std::array<int, n - 1> subI = {};
            for (int i = 1; i < n; i++)
                subI[i - 1] = I[i];
            return get<T, n - 1>(A[I[0]], subI);
        }
    }

    template<typename T, int n>
    tensor<n, T> reshape(const std::vector<T> &A, std::array<int, n> shape) {
        if constexpr (n == 0)
            return A[0];
        else {
            int m = A.size() / shape[0];
            std::vector<std::vector<T>> B(shape[0], std::vector<T>(m));
            for (int i = 0; i < shape[0]; i++)
                for (int j = 0; j < m; j++)
                    B[i][j] = A[i * m + j];
            tensor<n, T> R(shape[0]);
            std::array<int, n - 1> subshape = {};
            for (int i = 1; i < n; i++)
                subshape[i - 1] = shape[i];
            for (int i = 0; i < shape[0]; i++)
                R[i] = reshape<T, n - 1>(B[i], subshape);
            return R;
        }
    }

/*
 * Multidimensional Fast Fourier Transform
 * */

    template<int n, bool is_inverse = false>
    struct multidimensional_fft {
        std::array<int, n> shape;

        explicit multidimensional_fft(std::array<int, n> _shape) : shape(std::move(_shape)) {
        }

        template<typename ...R> requires (sizeof...(R) == n)
        explicit multidimensional_fft(R ..._shape) : shape({static_cast<int>(_shape)...}) {
        }


        using IC = std::complex<real>;

        tensor<n, IC> operator()(const tensor<n, IC> &T) const {
            tensor<n, IC> V(shape[0]);
            std::array<int, n - 1> subshape = {};
            for (int i = 1; i < n; i++)
                subshape[i - 1] = shape[i];
            multidimensional_fft<n - 1, is_inverse> subFFT(subshape);
            fast_fourier<is_inverse> FFT_1D(shape[0]);
            for (int i = 0; i < shape[0]; i++)
                V[i] = subFFT(T[i]);
            std::array<int, n - 1> S;
            for (auto &s: S)
                s = 0;
            std::vector<std::vector<IC>> R(shape[0]);
            do {
                std::vector<IC> Z;
                for (int i = 0; i < shape[0]; i++)
                    Z.push_back(get<IC, n - 1>(V[i], S));
                auto W = FFT_1D(Z);
                for (int i = 0; i < shape[0]; i++)
                    R[i].push_back(W[i]);
                int k;
                for (k = 0; k < n - 1 && S[k] == subshape[k] - 1; k++)
                    S[k] = 0;
                if (k < n - 1)
                    S[k]++;
            } while (std::any_of(S.begin(), S.end(), [](auto x) -> bool { return x > 0; }));
            tensor<n, IC> Y(shape[0]);
            for (int i = 0; i < shape[0]; i++)
                Y[i] = reshape<IC, n - 1>(R[i], subshape);
            return Y;
        }
    };

    template<int n, bool is_inverse = false>
    struct parallel_multidimensional_fft : public multidimensional_fft<n, is_inverse>, protected parallel_implementation {

        using parallel_implementation::HARD_CONCURRENCY;
        using parallel_implementation::SOFT_CONCURRENCY;
        using multidimensional_fft<n, is_inverse>::shape;
        using multidimensional_fft<n, is_inverse>::multidimensional_fft;

        using IC = std::complex<real>;

        tensor<n, IC> operator()(const tensor<n, IC> &T)  {
            tensor<n, IC> V(shape[0]);
            std::array<int, n - 1> subshape = {};
            for (int i = 1; i < n; i++)
                subshape[i - 1] = shape[i];
            std::vector<std::future<void>> futures;
            multidimensional_fft<n - 1, is_inverse> subFFT(subshape);
            auto L=shape[0]/SOFT_CONCURRENCY;
            parallel_fast_fourier<is_inverse> FFT_1D(shape[0]);
            for (int i = 0; i < SOFT_CONCURRENCY+1; i++)
                futures.emplace_back(std::async(std::launch::async,[&,i] ()
                    {
                        auto limit=(i==SOFT_CONCURRENCY?shape[0]%SOFT_CONCURRENCY:L);
                        for(int j=0;j<limit;j++)
                            V[i*L+j] = subFFT(T[i*L+j]);
                    }));
            for (auto &f: futures)
                f.get();
            std::array<int, n - 1> S;
            for (auto &s: S)
                s = 0;

            std::vector<std::vector<IC>> R(shape[0]);
            do {
                std::vector<IC> Z;
                for (int i = 0; i < shape[0]; i++)
                    Z.push_back(get<IC, n - 1>(V[i], S));
                auto W = FFT_1D(Z);
                for (int i = 0; i < shape[0]; i++)
                    R[i].push_back(W[i]);
                int k;
                for (k = 0; k < n - 1 && S[k] == subshape[k] - 1; k++)
                    S[k] = 0;
                if (k < n - 1)
                    S[k]++;
            } while (std::any_of(S.begin(), S.end(), [](auto x) -> bool { return x > 0; }));
            tensor<n, IC> Y(shape[0]);
            for (int i = 0; i < shape[0]; i++)
                Y[i] = reshape<IC, n - 1>(R[i], subshape);
            return Y;
        }
    };

    template<bool is_inverse>
    struct multidimensional_fft<0, is_inverse> {
        using IC = std::complex<real>;

        multidimensional_fft(std::array<int, 0> shape) {}

        tensor<0, IC> operator()(const tensor<0, IC> &O) const {
            return O;
        }
    };

    template<bool is_inverse>
    struct parallel_multidimensional_fft<0,is_inverse> : public multidimensional_fft<0,is_inverse>{};

/*
 * Fast Number Theoretic Transform (Fourier Transform over cyclic fields)
 * Suitable with fields IF of cardinality p such that totient(p) is a smooth number
 * */

    template<bool is_inverse = false>
    struct fast_ntt {
        int n, m;
        d_cyclic w;
        using IK = d_cyclic;
        inline static std::optional<std::reference_wrapper<factoriser>> F_ref = std::optional<std::reference_wrapper<factoriser>>();
    public:
        inline static bool use_normalized = true;

        static void set_factoriser(factoriser &F) {
            F_ref = F;
            fast_ntt<!is_inverse>::F_ref = F;
        }

        static factoriser &get_factoriser() {
            return F_ref.value();
        }

        fast_ntt(int _n, int _m) : n(_n), m(_m) {
            auto &F = this->F_ref.value().get();
            auto phi = F.totient(m);
            [[unlikely]]
            if (phi % n)
                throw std::domain_error("Fast NTT cannot be defined for this size");
            IK r = pow < IK > (primitive_root_of_unity(m, F), phi / n);
            if constexpr (is_inverse)
                w = r.inv();
            else w = r;
        }

        fast_ntt(int _n, int _m, d_cyclic _w) : n(_n), m(_m), w(_w) {
        }

        std::vector<IK> unnormalized(const std::vector<IK> &X) const {
            auto &F = this->F_ref.value().get();
            if (n == 1)
                return X;
            integer p = F.smallest_divisor(n), q = n / p;
            IK z = pow(w, q);
            fast_ntt<is_inverse> NTT(q, m, pow(w, p));
            std::vector<std::vector<IK>> U(p, std::vector<IK>(q));
            for (int i = 0; i < n; i++)
                U[i % p][i / p] = X[i];
            std::vector<std::vector<IK>> V(p);
            for (int i = 0; i < p; i++)
                V[i] = NTT.unnormalized(U[i]);
            std::vector<std::vector<IK>> Q(p, std::vector<IK>(q, 0));
            IK t = 1;
            for (int i = 0; i < p; i++, t *= z) {
                IK h1 = 1, h2 = 1;
                for (int j = 0; j < p; j++, h1 *= t, h2 *= w) {
                    IK h3 = 1;
                    for (int k = 0; k < q; k++, h3 *= h2)
                        Q[i][k] += h1 * h3 * V[j][k];
                }
            }
            std::vector<IK> R(n);
            for (int i = 0; i < p; i++)
                for (int j = 0; j < q; j++)
                    R[i * q + j] = Q[i][j];
            return R;
        }

        std::vector<IK> operator()(const std::vector<IK> &X) const {
            return unnormalized(X);
        }

        std::vector<IK> normalized(const std::vector<IK> &X) const {
            return unnormalized(X) / IK(n);
        }

        fast_ntt<!is_inverse> inv() const {
            return fast_ntt<!is_inverse>(n, m, w.inv());
        }
    };


/*
 * Fast Number Theoretic Transform (Fast Fourier Transform over cyclic fields)
 * Works only on "certain" powers of 2
 * Let p the cardinality of IF, let k the biggest integer such that 2^k | p-1:
 * => This version of NTT works only on vectors of a size s = 2^r with 0<=r<=k
 * */
    template<bool is_inverse = false>
    struct fast_ntt_base_2 : public fast_ntt<is_inverse> {
    public:
        using fast_ntt<is_inverse>::fast_ntt;
        using IK = typename fast_ntt<is_inverse>::IK;

        std::vector<d_cyclic> unnormalized(const std::vector<d_cyclic> &X) const {
            auto &n = this->n;
            auto &w = this->w;
            if (n == 1)
                return X;
            constexpr int p = 2;
            auto q = n / p;
            fast_ntt_base_2<is_inverse> FFT(q, d_cyclic::m, w * w);
            std::vector<IK> U1(q), U2(q);
            for (int i = 0; i < n; i += 2) {
                U1[i / p] = X[i];
                U2[i / p] = X[i + 1];
            }
            std::vector<IK> V1 = FFT.unnormalized(U1), V2 = FFT.unnormalized(U2);
            IC s = 1;
            for (int i = 0; i < q; i++, s *= w)
                V2[i] *= s;
            std::vector<IK> R(n);
            for (int i = 0; i < n / p; i++)
                R[i] = V1[i] + V2[i];
            for (int i = 0; i < n / p; i++)
                R[i + n / p] = V1[i] - V2[i];
            return R;
        }
    };

    using inverse_fast_ntt = fast_ntt<true>;

    inline std::vector<d_cyclic> fast_multiplication(std::vector<d_cyclic> x, std::vector<d_cyclic> y, int r_guess,
                                              factoriser &F = fast_ntt<>::get_factoriser()) {
        fast_ntt<>::set_factoriser(F);
        auto d_list = F.divisors_list(F.totient(d_cyclic::m));
        int r = *std::lower_bound(d_list.begin(), d_list.end(), r_guess);
        x.resize(r);
        y.resize(r);

        fast_ntt NTT(r, d_cyclic::m);
        inverse_fast_ntt INTT = NTT.inv();
        auto u = NTT(x), v = NTT(y);
        std::vector<d_cyclic> w(r);
        for (int i = 0; i < r; i++)
            w[i] = u[i] * v[i];
        auto z = INTT(w);
        auto h = d_cyclic(r).inv();
        for (auto &s: z)
            s *= h;
        z.resize(r_guess);
        return z;
    }

    inline std::vector<d_cyclic> fast_multiplication(std::vector<d_cyclic> x, std::vector<d_cyclic> y,
                                              factoriser &F = fast_ntt<>::get_factoriser()) {
        return fast_multiplication(x, y, x.size() + y.size() - 1, F);
    }

    inline polynomial <d_cyclic> fast_multiplication(const polynomial <d_cyclic> &x, const polynomial <d_cyclic> &y,
                                              factoriser &F = fast_ntt<>::get_factoriser()) {
        return fast_multiplication(static_cast<const std::vector<d_cyclic> &>(x),
                                   static_cast<const std::vector<d_cyclic> &>(y), F);
    }

    inline std::vector<integer> fast_multiplication(const std::vector<integer> &x, const std::vector<integer> &y,
                                             factoriser &F = fast_ntt<>::get_factoriser()) {
        constexpr integer L = 1e9;
        int n = x.size(), m = y.size();
        integer r = std::bit_ceil<unsigned int>(n + m - 1);
        integer k = ((L + r - 1) / r) * r;
        while (!F.is_prime(k + 1))
            k += r;
        d_cyclic::m = k + 1;
        std::vector<d_cyclic> u(x.size()), v(y.size());
        for (int i = 0; i < x.size(); i++)
            u[i] = x[i];
        for (int i = 0; i < y.size(); i++)
            v[i] = y[i];
        auto w = fast_multiplication(u, v, r, F);
        std::vector<integer> z(x.size() + y.size() - 1);
        for (int i = 0; i < z.size(); i++) {
            z[i] = (integer) w[i];
            if (z[i] > d_cyclic::m / 2)
                z[i] -= d_cyclic::m;
        }
        return z;
    }

    inline polynomial <integer> fast_multiplication(const polynomial <integer> &x, const polynomial <integer> &y,
                                             factoriser &F = fast_ntt<>::get_factoriser()) {
        return fast_multiplication(static_cast<const std::vector<integer> &>(x),
                                   static_cast<const std::vector<integer> &>(y), F);
    }
}
#endif //ACPC_PREPARATION_FFT_H
