//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ALGEBRA_TEST
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "nt/modular_arithmetic.h"
#include <boost/test/data/test_case.hpp>
#include "algebra/abstract_algebra.h"

using namespace algebra;
using namespace nt;
constexpr std::int64_t M = 1000000007;
constexpr int N = 100;
using IF=cyclic<M>;
using test_types=boost::mpl::list<int,long,long long,signed char,short,IF> ;
using test_long_types=boost::mpl::list<int,long long,IF>;
#include "../print.h"
namespace dataset=boost::unit_test::data;
constexpr real err=1e-6;

std::vector<integer> A={5,8,9,15,13,17,19,25,66,100},B={3,4,27,30,-13,-1,18,-500,99,102};

BOOST_AUTO_TEST_SUITE(test_abstract_algebra)


    BOOST_DATA_TEST_CASE(pow,dataset::make(A)^dataset::make(B),a,b)
    {
        BOOST_CHECK_CLOSE(algebra::pow<double>(b,a),std::pow(b,a),err);
    }

    BOOST_DATA_TEST_CASE(gcd,dataset::make(A)^dataset::make(B),a,b)
    {
        BOOST_CHECK_EQUAL(std::abs(algebra::gcd(a,b)),std::gcd(a,b));
        BOOST_CHECK_EQUAL(algebra::gcd(a,b),algebra::gcd(b,a));
    }

    BOOST_DATA_TEST_CASE(egcd,dataset::make(A)^dataset::make(B),a,b)
    {
        auto [u,v,d]=::egcd(a,b);
        BOOST_CHECK_EQUAL(u*a+v*b,d);
        BOOST_CHECK_EQUAL(std::gcd(a,b),std::abs(d));
    }

    BOOST_DATA_TEST_CASE(lcm,dataset::make(A)^dataset::make(B),a,b)
    {
        BOOST_CHECK_EQUAL(std::abs(algebra::lcm(a,b)),std::lcm(a,b));
        BOOST_CHECK_EQUAL(algebra::lcm(a,b),algebra::lcm(b,a));
    }

BOOST_AUTO_TEST_SUITE_END()
