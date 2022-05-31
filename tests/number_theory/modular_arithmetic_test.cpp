//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NUMBER_THEORY_TEST
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "nt/modular_arithmetic.h"
#include "../print.h"
using namespace nt;

constexpr std::int64_t M = 1000000007;
constexpr int N = 100;
using IF=cyclic<M>;
using test_types=boost::mpl::list<int,long,long long,signed char,short,IF> ;
using test_long_types=boost::mpl::list<int,long long,IF>;

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

BOOST_AUTO_TEST_SUITE(test_cyclic)
    BOOST_AUTO_TEST_SUITE(test_cyclic_constructor)
        BOOST_AUTO_TEST_CASE(test_cyclic_create)
        {
            cyclic<M> v1(6);
            BOOST_CHECK_EQUAL((integer&)v1, 6);
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(test_cyclic_operator)
        BOOST_AUTO_TEST_CASE(test_add_cyclic) {
            cyclic<M> v1(6);
            cyclic<M> v2(-7);
            BOOST_CHECK_EQUAL(v1+v2,M-1);
        }

        BOOST_AUTO_TEST_CASE(test_diff_cyclic) {
            cyclic<M> v1(6);
            cyclic<M> v2(-7);
            BOOST_CHECK_EQUAL(v1-v2,13);
        }

        BOOST_AUTO_TEST_CASE(test_scalar_cyclic)
        {
            cyclic<5> v1(6);
            BOOST_CHECK_EQUAL(7*v1,2);
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_negate)
        {
            cyclic<M> v1(6);
            BOOST_CHECK_EQUAL(-v1,M-6);
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_self_add)
        {
            cyclic<M> v1(6);
            cyclic<M> &v2=v1+=v1;
            BOOST_CHECK_EQUAL(std::addressof(v2),std::addressof(v1));
            BOOST_CHECK_EQUAL(v1,12);
        }
        BOOST_AUTO_TEST_CASE(test_cyclic_self_diff)
        {
            cyclic<M> v1(6);
            cyclic<M>&v2=v1-=v1;
            BOOST_CHECK_EQUAL(std::addressof(v2),std::addressof(v1));
            BOOST_CHECK_EQUAL(v1,0);
        }
        BOOST_AUTO_TEST_CASE(test_cyclic_mod_inverse)    {
            cyclic<101> v1(83);
            cyclic<101>::assume_prime=false;
            BOOST_CHECK_EQUAL(v1.inv(),28);
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_mod_inverse_rand_1e9_7)    {
            std::random_device dev;
            std::mt19937_64  rng(dev());
            std::uniform_int_distribution<integer> d(1,M-1);
            cyclic<M>::assume_prime=false;
            for(int i=0;i<N;i++)
            {
                cyclic<M> v1(d(rng));
                BOOST_CHECK_EQUAL(v1.inv()*v1,1);
            }
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_mod_pinverse_rand_1e9_4)    {
            std::random_device dev;
            std::mt19937_64  rng(dev());
            std::uniform_int_distribution<integer> d(1,M-1);
            constexpr auto M2=M-5;
            for(int i=0;i<N;i++)
            {
                integer r=d(rng);
                cyclic<M2> v1(r);
                BOOST_CHECK_EQUAL(v1.pinv()*v1,std::gcd(r,M2));
            }
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(test_cyclic_prime)
        BOOST_AUTO_TEST_CASE(test_cyclic_fermat)    {
            cyclic<M> v1(83);
            BOOST_CHECK_EQUAL(pow(v1,M-1),1);
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_log)    {
            cyclic<M> v1(83);
            cyclic<M> v2(pow(v1,15));
            BOOST_CHECK_EQUAL(discrete_log(v1,v2),15);
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_log_random)    {
            std::random_device dev;
            std::mt19937_64  rng(dev());
            std::uniform_int_distribution<integer> d(1,M/2);
            constexpr int N=100;
            for(int i=0;i<N;i++) {
                cyclic<M> v1(d(rng));
                integer r=d(rng);
                cyclic<M> v2(pow(v1, r));
                BOOST_CHECK_EQUAL(discrete_log(v1, v2), r);
            }
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_sqrt)    {
            cyclic<M> v1(83);
            cyclic<M> v2(pow(v1,2));
            BOOST_CHECK_EQUAL(nt::sqrt(v2),v1);
        }

        BOOST_AUTO_TEST_CASE(test_cyclic_sqrt_random)    {
            std::random_device dev;
            std::mt19937_64  rng(dev());
            std::uniform_int_distribution<integer> d(0,M-1);
            constexpr int N=100;
            for(int i=0;i<N;i++) {
                cyclic<M> v1(d(rng));
                cyclic<M> v2=v1*v1,v3=sqrt(v2);
                BOOST_CHECK_EQUAL(v3*v3, v1*v1);
            }
        }

       /* BOOST_AUTO_TEST_CASE(test_cyclic_sqrt_random_full)    {
            std::random_device dev;
            std::mt19937_64  rng(dev());
            std::uniform_int_distribution<integer> d(1,M-1);
            constexpr int N=100;
            for(int i=0;i<N;i++) {
                cyclic<M> v1(d(rng));
                cyclic<M> v2=v1*v1,v3=sqrt(v2);
                BOOST_CHECK_EQUAL(v3*v3, v1*v1);
            }
        }*/
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
