//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LINEAR_ALGEBRA_TEST
#include "linear_algebra/linear_algebra.h"
#include <boost/mpl/list.hpp>
#include "nt/modular_arithmetic.h"

using namespace nt;
using namespace algebra;
using namespace linalg;
constexpr integer M = 1000000007;
constexpr int N = 100;
using IF=cyclic<M>;
using test_types=boost::mpl::list<int,long,long long,signed char,short> ;
using test_long_types=boost::mpl::list<int,long long>;


#include <boost/test/unit_test.hpp>
#include "../print.h"


namespace boost::test_tools
{
    template<typename T,int n,int m>
    struct tt_detail::print_log_value<s_matrix<T,n,m> >
    {
        void operator()( std::ostream& os, s_matrix<T,n,m> const& ts)
        {
            ::operator<<(os, ts);
        }
    };
    template<typename T,int n>
    struct tt_detail::print_log_value<s_vector<T,n> >
    {
        void operator()( std::ostream& os, s_vector<T,n> const& ts)
        {
            ::operator<<(os,ts);
        }
    };

    template<algebra::integer n>
    struct tt_detail::print_log_value<cyclic<n> > {
        void operator()( std::ostream& os, cyclic<n> const& ts)
        {
            os << (algebra::integer)ts;
        }
    };
}

BOOST_AUTO_TEST_SUITE(test_vector)
    BOOST_AUTO_TEST_SUITE(test_vector_constructor)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_vector_create,T,test_types)
        {
            s_vector<T, 5> v1({1, 2, 3, 4, 5});
            BOOST_CHECK_EQUAL(v1[0], 1U);
            BOOST_CHECK_EQUAL(v1[1], 2U);
            BOOST_CHECK_EQUAL(v1[2], 3U);
            BOOST_CHECK_EQUAL(v1[3], 4U);
            BOOST_CHECK_EQUAL(v1[4], 5U);
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(test_vector_operator)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_add_vector,T,test_types) {
            s_vector<T,5> v1({1,2,3,4,5});
            s_vector<T,5> v2({3,7,-1,-2,2});
            s_vector<T,5> v3({4,9,2,2,7});
            BOOST_CHECK_EQUAL(v1+v2,v3);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_diff_vector,T,test_types) {
            s_vector<T,5> v1({1,2,3,4,5});
            s_vector<T,5> v2({3,7,-1,-2,2});
            s_vector<T,5> v3({-2,-5,4,6,3});
            BOOST_CHECK_EQUAL(v1-v2,v3);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_vector,T,test_types)
        {
            s_vector<T,5> v1({1,2,3,4,5});
            s_vector<T,5> v2({3,6,9,12,15});
            BOOST_CHECK_EQUAL(T(3)*v1,v2);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_vector_negate,T,test_types)
        {
            s_vector<T,5> v1({1,2,3,4,5});
            s_vector<T,5> v2({-1,-2,-3,-4,-5});
            BOOST_CHECK_EQUAL(-v1,v2);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_vector_self_add,T,test_types)
        {
            s_vector<T,5> v1({1,2,3,4,5});
            s_vector<T,5> v2({-1,-2,-3,-4,-5});
            s_vector<T,5>&v3=v1+=v2;
            s_vector<T,5> v4;
            BOOST_CHECK_EQUAL(std::addressof(v1),std::addressof(v3));
            BOOST_CHECK_EQUAL(v1,v4);
        }
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_vector_self_diff,T,test_types)
        {
            s_vector<T,5> v1({1,2,3,4,5});
            s_vector<T,5> v2=v1;
            s_vector<T,5>&v3=v1-=v2;
            s_vector<T,5> v4;
            BOOST_CHECK_EQUAL(std::addressof(v1),std::addressof(v3));
            BOOST_CHECK_EQUAL(v1,v4);
        }
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_matrix)
    BOOST_AUTO_TEST_SUITE(test_matrix_constructor)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_create,T,test_types){
            s_matrix<T,2,2> m1({{1,2},{3,4}});
            s_matrix<T,2,2> m2({{1,2},{3,4}});

            BOOST_CHECK_EQUAL(m1[0][0],1U);
            BOOST_CHECK_EQUAL(m1[0][1],2U);
            BOOST_CHECK_EQUAL(m1[1][0],3U);
            BOOST_CHECK_EQUAL(m1[1][1],4U);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(test_matrix_operator)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_add,T,test_types) {
        s_matrix<T,2,2> M1({{1,2},{3,4}});
        s_matrix<T,2,2> M2({{3,7},{-1,-2}});
        s_matrix<T,2,2> M3({{4,9},{2,2}});
        BOOST_CHECK_EQUAL(M1+M2, M3);
    }
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_diff,T,test_types) {
            s_matrix<T,2,2> M1({{1,2},{3,4}});
            s_matrix<T,2,2> M2({{3,7},{-1,-2}});
            s_matrix<T,2,2> M3({{-2,-5},{4,6}});
            BOOST_CHECK_EQUAL(M1-M2, M3);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_scalar,T,test_types)
        {
            s_matrix<T,2,2> M1({{1,2},{3,4}});        s_matrix<int,2,2> m1({{1,2},{3,4}});

            s_matrix<T,2,2> M2({{3,6},{9,12}});
            BOOST_CHECK_EQUAL(T(3)*M1,M2);
        }
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_negate,T,test_types)
        {
            s_matrix<T,2,2> M1({{1,2},{3,4}});
            s_matrix<T,2,2> M2({{-1,-2},{-3,-4}});
            BOOST_CHECK_EQUAL(-M1,M2);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_mult,T,test_types)
        {
            s_matrix<T,2,2> M1({{1,2},{3,4}});
            s_matrix<T,2,2> M2({{1,2},{3,4}});
            s_matrix<T,2,2> M3({{7,10},{15,22}});
            BOOST_CHECK_EQUAL(M1*M2,M3);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_self_mult,T,test_types)
        {
            s_matrix<T,2,2> M1({{1,2},{3,4}});
            s_matrix<T,2,2> M2({{1,2},{3,4}});
            s_matrix<T,2,2> &M3=M1*=M2;
            BOOST_CHECK_EQUAL(std::addressof(M3),std::addressof(M1));
            BOOST_CHECK_EQUAL(M1,M2*M2);
        }
    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_pow,T,test_long_types)
    {
        s_matrix<T,4,4> A({{1,2,3,4},{3,1,2,4},{1,4,3,1},{5,3,1,2}});
        s_matrix<T,4,4> B({{271373769, 257707107, 229627054, 291157093},
                           {274537505, 260711810, 232288922, 294525263},
                           {236529470, 224618247, 200110798, 253716959},
                           {299967605, 284862168, 253759121, 321726562}});
        BOOST_CHECK_EQUAL(pow(A,9),B);
    }
    BOOST_AUTO_TEST_SUITE(test_matrix_linalg)
        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_vector,T,test_types)
        {
            s_matrix<T,3,4> A({{1,2,3,4},{3,1,2,4},{1,4,3,1}});
            s_vector<T,4> u({2,1,3,1});
            s_vector<T,3> v({17,17,16});
            BOOST_CHECK_EQUAL(A*u,v);
        }
        BOOST_AUTO_TEST_CASE(test_matrix_det)
        {
            s_matrix<IF,4,4> A({{1,2,3,4},{3,1,2,4},{1,4,3,1},{5,3,1,2}});
            BOOST_CHECK_EQUAL(A.det(),35U);
        }

        BOOST_AUTO_TEST_CASE_TEMPLATE(test_matrix_trace,T,test_types)
        {
            s_matrix<T,4,4> A({{1,2,3,4},{3,1,2,4},{1,4,3,1},{5,3,1,2}});
            BOOST_CHECK_EQUAL(A.tr(),7U);
        }

        BOOST_AUTO_TEST_CASE(test_matrix_inv)
        {
            s_matrix<IF,4,4> A({{1,2,3,4},{3,1,2,4},{1,4,3,1},{5,3,1,2}});
            BOOST_CHECK_EQUAL(A*A.inv(),decltype(A)(1));
        }

        BOOST_AUTO_TEST_CASE(test_matrix_inv_rand)
        {
            std::random_device dev;
            std::mt19937_64 rng(dev());
            std::uniform_int_distribution<integer> d(0,M-1);
            for(int i=0;i<N;i++) {
                s_matrix<IF, 100, 100> A;
                for (auto &R: A)
                    for (auto &c: R)
                        c = d(rng);
                if(A.det()!=0)
                    BOOST_CHECK_EQUAL(A * A.inv(), decltype(A)(1));
            }
        }
    BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE_END()
