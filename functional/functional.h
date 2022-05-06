//
// Created by ramizouari on 01/12/2021.
//

#ifndef __FUNCTIONAL_H__
#define __FUNCTIONAL_H__
#include <concepts>
#include <utility>

namespace functional {
    template<typename F, typename M>
    concept MonoidOperation = requires(F f, M a, M b)
    {
        { f(a, b) }->std::convertible_to<M>;
        { F::neutral }->std::convertible_to<M>;
    };

    template<typename F, typename M>
    concept Endomorphism = std::is_same_v<decltype(std::declval<F>()(std::declval<M>())), M>;

    template<typename T>
    concept Iterable = requires(T t)
    {
        { t.begin() }->std::convertible_to<typename T::iterator>;
        { t.end() }->std::convertible_to<typename T::iterator>;
    };

    template<typename T>
    struct base_type_t
    {
        using base_type = T;
    };
    template <Iterable T>
    struct base_type_t<T>
    {
            using base_type= typename base_type_t<decltype(*std::declval<T>().begin())>::base_type;
    };

    template<typename T>
    using base_type = typename base_type_t<T>::base_type;

    template<typename M, typename O, typename G = typename M::base_field>
    void apply_pointwise(const O &f, M &u) requires Endomorphism<O, G> {
        if constexpr (std::is_same_v<G, M>)
            u = f(u);
        else
            for (auto &w: u)
                apply_pointwise<std::remove_reference_t<decltype(w)>, O, G>(f, w);
    }

    template<typename M, typename O, typename G = typename M::base_field>
    void apply_pointwise(const O &f, M &u, M a, M b) requires MonoidOperation<O, G> {
        if constexpr (std::is_same_v<G, M>)
            u = f(a, b);
        else
            for (auto [p, s, t]: zip<M, M, M>(std::forward<M>(u), std::forward<M>(a), std::forward<M>(b)))
                apply_pointwise<std::remove_reference_t<decltype(p)>, O, G>(f, p, s, t);
    }

    template<typename M, typename O, typename G = typename M::base_field>
    M pointwise_function(const O &f, M u) requires Endomorphism<O, G> {
        apply_pointwise<M, O, G>(f, u);
        return u;
    }

    template<typename M, typename O, typename G = typename M::base_field>
    M pointwise_function(const O &f, M u, M a, M b) requires Endomorphism<O, G> {
        apply_pointwise<M, O, G>(f, u, a, b);
        return u;
    }

    template<typename M, typename Function, typename G = base_type<M>>
    void foreach(const Function &f, M &u) {
        if constexpr (std::is_same_v<G, M>)
            f(u);
        else
            for (auto &p: u)
                foreach<std::remove_reference_t<decltype(p)>, Function, G>(f, p);
    }

    template<typename M, typename Function, typename G = base_type<M>>
    void foreach(const Function &f, M &&u) {
        if constexpr (std::is_same_v<G, M>)
            f(u);
        else
            for (auto &&p: u)
                foreach<std::remove_reference_t<decltype(p)>, Function, G>(f, std::move(p));
    }

    template<typename M, typename Homeomorphism,
            typename O, typename G = typename M::base_field>
    decltype(O::neutral) pointwise_aggregate(const O &f, const Homeomorphism &h, M u)requires MonoidOperation<O, G> {
        auto result = O::neutral;
        if constexpr (std::is_same_v<G, M>)
            result = h(u);
        else
            for (auto p: u)
                result = f(
                        result,
                        pointwise_aggregate<std::remove_reference_t<decltype(p)>, Homeomorphism, O, G>(f, h, p)
                );
        return result;
    }

    template<typename M, typename O, typename G = typename M::base_field>
    G pointwise_reduce(const O &f, M u) requires MonoidOperation<O, G> {
        auto neutral = O::neutral;
        if constexpr (std::is_same_v<G, M>)
            neutral = f(neutral, u);
        else
            for (auto p: u)
                neutral = f(neutral, pointwise_reduce<std::remove_reference_t<decltype(p)>, O, G>(f, p));
        return neutral;
    }
}
#endif //ACPC_PREPARATION_ABSTRACT_ALGEBRA_H
