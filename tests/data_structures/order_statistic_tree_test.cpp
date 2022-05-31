//
// Created by ramizouari on 30/05/22.
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
#include "data_structures/statistic_tree.h"
#include "nt/modular_arithmetic.h"
#include "linear_algebra/linear_algebra.h"
using namespace linalg;
using namespace nt;
using namespace data_structures;
constexpr int N = 100;
constexpr int M=1e6;
using test_types=boost::mp11::mp_list<int,long long> ;

#include "../print.h"


template<typename T>
concept is_iterable = requires(const T&a)
{
    a.begin();
    a.end();
};

template<typename T,typename O>
concept is_invertible = std::is_base_of<invertible_operation<T>,O>::value;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& a)
{
    os << "[";
    for(auto& x:a)
        os << x << ",";
    os << "]";
    return os;
}


namespace boost::test_tools {
    template<typename T>
    struct tt_detail::print_log_value<std::vector<T> > {
        void operator()( std::ostream& os,
                         std::vector<T> const& ts)
        {
            os << "BI";
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

template<typename A>
struct ost_fixture
{
    inline static constexpr int N=1e4;
    inline static constexpr int Q=1e3;
    std::vector<A> data;
    order_node<A> *S;

    static ost_fixture&  get_instance()
    {
        if(instance==nullptr)
            instance.reset( new ost_fixture());
        return *instance;
    }

    int test_implementation(int Q= ost_fixture::Q)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> distribution(0,Q);
        std::uniform_int_distribution<int> d2(0,N-1);
        int wrong_counter=0;
        for(int i=0;i<Q;++i)
        {
            int k=d2(rng);
            auto actual= data_structures::select(S,k)->v;
            auto expected = data[k];
            if(expected!=actual)
                ++wrong_counter;
        }
        return wrong_counter;
    }

    int test_implementation_with_update(double p, int Q= ost_fixture::Q)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> distribution(0,Q);
        std::uniform_int_distribution<int> d2(0,N-1);
        std::bernoulli_distribution bernoulliDistribution(p);
        int wrong_counter=0;
        for(int i=0;i<Q;++i)
        {
            if (bernoulliDistribution(rng))
            {
                int k=d2(rng);
                auto actual= data_structures::select(S,k)->v;
                auto expected = data[k];
                if(expected!=actual)
                    ++wrong_counter;
            }
            else
            {
                int idx = d2(rng);
                S=data_structures::erase(S,data_structures::find(S,data[idx])->v);
                data[idx] = generate_random<A>(distribution, rng);
                S=data_structures::insert(S,data[idx]);
                std::sort(data.begin(),data.end());

                auto expected = data[idx];
                auto actual= data_structures::select(S,idx)->v;
                if (expected != actual)
                    ++wrong_counter;
            }
        }
        return wrong_counter;
    }
private:
    ost_fixture(): data(random_vector(N, std::uniform_int_distribution<integer>{0, M - 1}, std::mt19937_64{std::random_device{}()})), S(nullptr)
    {
        for(auto s:data)
            S=data_structures::insert(S,s);
        std::sort(data.begin(),data.end());
    }
    inline static std::unique_ptr<ost_fixture> instance;
    inline static std::vector<A> random_vector(int n,auto &&distribution,auto &&rng)
    {
        return generate_random_vector<A>(n,distribution,rng);
    }
};

BOOST_AUTO_TEST_SUITE(test_ost)
    BOOST_AUTO_TEST_SUITE(query)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query_plus,T,test_types)
        {
            auto& fixture=ost_fixture<T>::get_instance();
            auto wrong_counter=fixture.test_implementation();
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(query_update)
        using test_types_with_p = boost::mp11::mp_product<std::tuple,test_types,boost::mp11::mp_list_c<int,1,2,5,10,20,50,75>>;

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_query,U,test_types_with_p)
        {
            using T=typename std::tuple_element<0,U>::type;
            using K=typename std::tuple_element<1,U>::type;
            double p=K::value;
            p/=100;
            auto& fixture=ost_fixture<T>::get_instance();
            auto wrong_counter=fixture.test_implementation_with_update(p);
            BOOST_CHECK_EQUAL(wrong_counter,0);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()