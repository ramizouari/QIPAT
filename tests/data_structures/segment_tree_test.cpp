//
// Created by ramizouari on 12/04/2022.
//
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <random>
#include <chrono>
#include "data_structures/data_structures.h"
#include "nt/modular_arithmetic.h"
#include "linear_algebra/linear_algebra.h"
using namespace linalg;
using namespace nt;
using namespace data_structures;
constexpr std::int64_t M = 1000000007;
constexpr int N = 100;
using IF=cyclic<M>;
using IM=s_matrix<IF,3,3>;
using test_types=boost::mp11::mp_list<long long,IF,cyclic<17>,IM> ;
using comparable_test_types=boost::mp11::mp_list<long long,int>;


#include "../print.h"


template<typename T>
concept is_iterable = requires(const T&a)
{
    a.begin();
    a.end();
};

template<typename T,typename O>
concept is_invertible = std::is_base_of<invertible_operation<T>,O>::value;

namespace boost::test_tools {
    template<typename T>
    struct tt_detail::print_log_value<std::vector<T> > {
        void operator()( std::ostream& os,
                         std::vector<T> const& ts)
        {
            os << ts;
        }
    };
}

template<typename T>
T generate_random(auto &distrubtion,auto &rng)
{
    if constexpr (is_iterable<T>)
    {
        T res;
        for(auto& x:res)
            x= generate_random<std::remove_reference_t<decltype(x)>>(distrubtion,rng);
        return res;
    }
    else
        return distrubtion(rng);
}

template<typename T>
std::vector<T> generate_random_vector(int n,auto &distribution,auto &rng)
{
    std::vector<T> v(n);
    for(int i=0;i<n;++i)
        v[i]= generate_random<T>(distribution,rng);
    return v;
}

template<typename A,typename O>
struct segment_tree_fixture
{
    inline static constexpr O F{};
    inline static constexpr int N=1e6;
    inline static constexpr int Q=1e6;
    std::vector<A> data;
    segment_tree<A,O> S;

    static segment_tree_fixture&  get_instance()
    {
        if(instance==nullptr)
            instance.reset( new segment_tree_fixture());
        return *instance;
    }

    int test_implementation(int width = segment_tree_fixture::N,int Q= segment_tree_fixture::Q)
    {
        auto cumulative=data;
        for(int i=1;i<N;i++)
            cumulative[i]=F(cumulative[i],cumulative[i-1]);
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> distribution(0,Q);
        std::uniform_int_distribution<int> d2(0,width);
        int wrong_counter=0;
        for(int i=0;i<Q;++i)
        {
            int l=d2(rng);
            int r=d2(rng);
            if(l>r)
                std::swap(l,r);
            auto expected=O::neutral;
            if constexpr (is_invertible<A,O>)
                expected=F(cumulative[r-1],F.inv(l==0?O::neutral:cumulative[l-1]));
            else
                expected = std::reduce(data.begin()+l,data.begin()+r,O::neutral,F);
            auto actual=S.query(l,r);
            if(expected!=actual)
                ++wrong_counter;
        }
        return wrong_counter;
    }

    int test_implementation_with_update(double p,int width = segment_tree_fixture::N,int Q= segment_tree_fixture::Q)
    {
        auto cumulative=data;
        for(int i=1;i<N;i++)
            cumulative[i]=F(cumulative[i],cumulative[i-1]);
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> distribution(0,Q);
        std::uniform_int_distribution<int> d2(0,width);
        std::bernoulli_distribution B(p);
        int wrong_counter=0;
        for(int i=0;i<Q;++i)
        {
            if (B(rng))
            {
                int l = d2(rng);
                int r = d2(rng);
                if (l > r)
                    std::swap(l, r);
                auto expected = O::neutral;
                expected = std::reduce(data.begin()+l,data.begin()+r,O::neutral,F);
                auto actual = S.query(l, r);
                if (expected != actual)
                    ++wrong_counter;
            }
            else
            {
                int idx = distribution(rng);
                data[idx] = generate_random<A>(distribution, rng);
                S.update(idx, data[idx]);
                auto expected = data[idx];
                auto actual = S.query(idx, idx + 1);
                if (expected != actual)
                    ++wrong_counter;
            }
        }
        return wrong_counter;
    }
private:
    segment_tree_fixture(): data(random_vector(N, std::uniform_int_distribution<integer>{0, M - 1}, std::mt19937_64{std::random_device{}()})), S(data)
    {
    }
    inline static std::unique_ptr<segment_tree_fixture> instance;
    inline static std::vector<A> random_vector(int n,auto &&distribution,auto &&rng)
    {
       return generate_random_vector<A>(n,distribution,rng);
    }
};

BOOST_AUTO_TEST_SUITE(test_segment_tree)
    BOOST_AUTO_TEST_SUITE(query)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_plus,T,test_types)
        {
            auto& fixture=segment_tree_fixture<T,plus_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation();
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_max,T,comparable_test_types)
        {
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,max_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation(W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_min,T,comparable_test_types)
        {
            min_t<T>::neutral=std::numeric_limits<T>::max();
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,min_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation(W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_times,T,test_types)
        {
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,multiplies_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation(W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(query_update)
        using test_types_with_p = boost::mp11::mp_product<std::tuple,test_types,boost::mp11::mp_list_c<int,1,10,25,50,75>>;
        using comparable_test_types_with_p = boost::mp11::mp_product<std::tuple,comparable_test_types ,boost::mp11::mp_list_c<int,1,10,25,50,75>>;

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_plus,U,test_types_with_p)
        {
            using T=typename std::tuple_element<0,U>::type;
            using K=typename std::tuple_element<1,U>::type;
            double p=K::value;
            p/=100;
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,plus_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation_with_update(p,W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_max,U,comparable_test_types_with_p)
        {
            using T=typename std::tuple_element<0,U>::type;
            using K=typename std::tuple_element<1,U>::type;
            double p=K::value;
            p/=100;
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,max_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation_with_update(p,W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_min,U,comparable_test_types_with_p)
        {
            using T=typename std::tuple_element<0,U>::type;
            using K=typename std::tuple_element<1,U>::type;
            double p=K::value;
            p/=100;
            min_t<T>::neutral=std::numeric_limits<T>::max();
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,min_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation_with_update(p,W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_times,U,test_types_with_p)
        {
            using T=typename std::tuple_element<0,U>::type;
            using K=typename std::tuple_element<1,U>::type;
            double p=K::value;
            p/=100;
            constexpr int W=1000;
            auto& fixture=segment_tree_fixture<T,multiplies_t<T>>::get_instance();
            auto wrong_counter=fixture.test_implementation_with_update(p,W);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()