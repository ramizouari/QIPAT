//
// Created by ramizouari on 12/04/2022.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE POLYNOMIAL_TEST
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "polynomial/polynomial.h"
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "nt/modular_arithmetic.h"
#include <random>
#include <chrono>
using namespace poly;
using namespace nt;
constexpr std::int64_t M = 1000000007;
constexpr int N = 100;
using IF=cyclic<M>;
using test_types=boost::mpl::list<long,long long,signed char,short,IF> ;
using long_types=boost::mpl::list<long,long long,IF> ;


#include "../print.h"

namespace boost::test_tools {
    template<algebra::integer n>
    struct tt_detail::print_log_value<cyclic<n> > {
    void operator()( std::ostream& os,
                     cyclic<n> const& ts)
    {
        os  << (algebra::integer&)ts;
    }
};
}


namespace dataset=boost::unit_test::data;
namespace interpolation_data
{
    std::vector<std::vector<IF>> X{
        {0,1,2,3,4},
        {0,1,2,3,4,5,6,7,8,9,10}
        },
        Y={
            {1,2,5,10,17},
            {1,2,4,8,16,32,64,128,256,512,1024}
    };
    std::vector<std::vector<IF>> P({
        {1,0,1},
        {1,IF(1627)/IF(2520),IF(19013)/IF(50400),IF(-2729)/IF(25920),IF(8161)/IF(72576),
                                       IF(-1339)/IF(34560),IF(1753)/IF(172800),IF(-193)/IF(120960),IF(1)/IF(6048),
                                       IF(-1)/IF(103680),IF(1)/IF(3628800)}
    });
}


namespace boost::test_tools {
    template<typename T>
    struct tt_detail::print_log_value<std::vector<T> > {
        void operator()( std::ostream& os,
                         std::vector<T> const& ts)
        {
            ::operator<<(os,ts);
        }
    };
}

namespace boost::test_tools {
    template<typename T>
    struct tt_detail::print_log_value<poly::polynomial<T> > {
        void operator()( std::ostream& os,
                         poly::polynomial<T> const& ts)
        {
            ::operator<<(os,ts);
        }
    };
}

template<typename T>
std::vector<T> generate_random_vector(int n,auto &distribution,auto &rng)
{
    std::vector<T> v(n);
    for(int i=0;i<n;++i)
        v[i]=distribution(rng);
    return v;
}


BOOST_AUTO_TEST_SUITE(test_polynomial)
    BOOST_AUTO_TEST_SUITE(test_polynomial_constructor)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_polynomial_create,T,test_types)
        {
            BOOST_TEST_MESSAGE("Testing polynomial Construction");
            polynomial<T> v1({1, 2, 3, 4, 5});
            BOOST_CHECK_EQUAL(v1[0], 1);
            BOOST_CHECK_EQUAL(v1[1], 2);
            BOOST_CHECK_EQUAL(v1[2], 3);
            BOOST_CHECK_EQUAL(v1[3], 4);
            BOOST_CHECK_EQUAL(v1[4], 5);
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(test_polynomial_operator)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_add_polynomial,T,test_types) {
            BOOST_TEST_MESSAGE("Testing polynomial addition");
            polynomial<T> v1({1,2,3,4,5});
            polynomial<T> v2({3,7,-1,-2,2});
            polynomial<T> v3({4,9,2,2,7});
            BOOST_CHECK_EQUAL(v1+v2,v3);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_diff_polynomial,T,test_types) {
            BOOST_TEST_MESSAGE("Testing polynomial difference");
            polynomial<T> v1({1,2,3,4,5});
            polynomial<T> v2({3,7,-1,-2,2});
            polynomial<T> v3({-2,-5,4,6,3});
            BOOST_CHECK_EQUAL(v1-v2,v3);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_polynomial,T,test_types)
        {
            BOOST_TEST_MESSAGE("Testing polynomial scalar multiplication");
            polynomial<T> v1({1,2,3,4,5});
            polynomial<T> v2({3,6,9,12,15});
            BOOST_CHECK_EQUAL(T(3)*v1,v2);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_polynomial_negate,T,test_types)
        {
            BOOST_TEST_MESSAGE("Testing polynomial additive inverse");
            polynomial<T> v1({1,2,3,4,5});
            polynomial<T> v2({-1,-2,-3,-4,-5});
            BOOST_CHECK_EQUAL(-v1,v2);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_polynomial_self_add,T,test_types)
        {
            BOOST_TEST_MESSAGE("Testing polynomial inplace addition");
            polynomial<T> v1({1,2,3,4,5});
            polynomial<T> v2({-1,-2,-3,-4,-5});
            polynomial<T>&v3=v1+=v2;
            polynomial<T> v4;
            BOOST_CHECK_EQUAL(std::addressof(v1),std::addressof(v3));
            BOOST_CHECK_EQUAL(v1,v4);
        }


        BOOST_AUTO_TEST_SUITE(test_polynomial_mult)
            BOOST_AUTO_TEST_CASE_TEMPLATE(naive,T,test_types)
            {
                BOOST_TEST_MESSAGE("Testing polynomial multiplication");
                polynomial<T> v1({1,1,1,1,1});
                polynomial<T> v2({1,-2,3,-4,5});
                polynomial<T>v3({1,-1,2,-2,3,2,4,1,5});
                BOOST_CHECK_EQUAL(v1*v2,v3);
            }
            BOOST_AUTO_TEST_CASE_TEMPLATE(self_multiply,T,test_types)
            {
                BOOST_TEST_MESSAGE("Testing polynomial inplace multiplication");
                polynomial<T> v1({1,1,1,1,1});
                polynomial<T> v2({1,-2,3,-4,5});
                polynomial<T>v4({1,-1,2,-2,3,2,4,1,5});
                polynomial<T>&v3=v1*=v2;
                BOOST_CHECK_EQUAL(std::addressof(v1),std::addressof(v3));
                BOOST_CHECK_EQUAL(v1,v4);
            }

            BOOST_AUTO_TEST_CASE_TEMPLATE(karatsuba,T,long_types)
            {
                BOOST_TEST_MESSAGE("Testing karatsuba' multiplication");
                constexpr int N=100;
                constexpr int degree=1000;
                std::random_device dev;
                std::mt19937_64 rng(dev());
                std::uniform_int_distribution<integer> d(0,M-1);
                for(int i=0;i<N;i++) {
                    polynomial<T> v1(generate_random_vector<T>(degree+1,d,rng));
                    polynomial<T> v2(generate_random_vector<T>(degree+1,d,rng));
                    polynomial<T> v3=v1*v2;
                    BOOST_CHECK_EQUAL(v3, karatsuba_multiplication(v1,v2));
                }
            }

            BOOST_AUTO_TEST_CASE_TEMPLATE(karatsuba_speed,T,long_types)
            {
                BOOST_TEST_MESSAGE("Testing Karatsuba's multiplication speed");
                constexpr int N=10;
                constexpr int degree=50000;
                std::random_device dev;
                std::mt19937_64 rng(dev());
                std::uniform_int_distribution<integer> d(0,M-1);
                using namespace std::chrono_literals;

                for(int i=0;i<N;i++) {
                    polynomial<T> v1(generate_random_vector<T>(degree+1,d,rng));
                    polynomial<T> v2(generate_random_vector<T>(degree+1,d,rng));
                        auto t1=std::chrono::high_resolution_clock::now();
                    polynomial<T> v3=karatsuba_multiplication(v1,v2);
                        auto t2=std::chrono::high_resolution_clock::now();
                    BOOST_CHECK(t2-t1<1s);
                    BOOST_TEST_MESSAGE("Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms");
                }
            }
        BOOST_AUTO_TEST_SUITE_END()

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_polynomial_self_diff,T,test_types)
        {
            polynomial<T> v1({1,2,3,4,5});
            polynomial<T> v2=v1;
            polynomial<T>&v3=v1-=v2;
            polynomial<T> v4;
            BOOST_CHECK_EQUAL(std::addressof(v1),std::addressof(v3));
            BOOST_CHECK_EQUAL(v1,v4);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_polynomial_evaluation,T,test_types)
        {
            polynomial<T> v1({1,2,3,4,5,6});
            BOOST_CHECK_EQUAL(v1(T(0)),T(1));
            BOOST_CHECK_EQUAL(v1(T(1)),T(21));
            BOOST_CHECK_EQUAL(v1(T(2)),T(321));
            BOOST_CHECK_EQUAL(v1(T(3)),T(2005));
            BOOST_CHECK_EQUAL(v1(T(-1)),T(-3));
            BOOST_CHECK_EQUAL(v1(T(-2)),T(-135));

        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(test_polynomial_interpolation)
        BOOST_DATA_TEST_CASE(test_polynomial_newton,dataset::make(interpolation_data::X)^dataset::make(interpolation_data::Y)^dataset::make(interpolation_data::P)
                             ,x,y,z)
        {
            BOOST_CHECK_EQUAL(newton_interpolation(x,y),z);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
