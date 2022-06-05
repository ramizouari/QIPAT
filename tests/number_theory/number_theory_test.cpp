//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "nt/number_theory.h"
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
using namespace nt;
constexpr std::int64_t M = 1000000007;
constexpr int N = 1000;

#include "../print.h"


constexpr int L=1e6;

namespace dataset=boost::unit_test::data;

struct factoriser_fixture
{
    factoriser F;
    factoriser_fixture():F(L)
    {
    }
};




namespace boost::test_tools {
    template<typename T>
    struct tt_detail::print_log_value<std::vector<T> > {
        void operator()( std::ostream& os,
                         std::vector<T> const& ts)
        {
            ::operator<<(os,ts);
        }
    };

    template<typename A,typename  B>
    struct tt_detail::print_log_value<std::pair<A,B> > {
        void operator()( std::ostream& os,
                         std::pair<A,B> const& ts)
        {
            ::operator<<(os,ts);
        }
    };
}

std::vector<integer> factorisation_data{10000,100001,314159,510510};

std::vector<std::vector<integer>> factorisation_result={std::vector<integer>{2,5},{11,9091},{314159},{2,3,5,7,11,13,17}};
std::vector<std::vector<std::pair<integer,integer>>> decomposition_result={std::vector<std::pair<integer,integer>>{{2,1},{5,1}},{{11,1},{9091,1}},{{314159,1}},{{2,1},{3,1},{5,1},{7,1},{11,1},{13,1},{17,1}}};
std::vector<integer> totient_result={4000,90900,314158,92160};
std::vector<std::vector<integer>> divisors_result=
        {
                {1,2,4,5,8,10,16,20,25,40,50,80,100,125,200,250,400,500,625,1000,1250,2000,2500,5000,10000},
                {1,11,9091,100001},
                {1,314159},
                {1,2,3,5,6,7,10,11,13,14,15,17,21,22,26,30,33,34,35,39,42,51,55,65,66,70,77,78,85,91,102,105,110,119,130,143,154,165,170,182,187,195,210,
                        221,231,238,255,273,286,330,357,374,385,390,429,442,455,462,510,546,561,595,663,714,715,770,858,910,935,1001,1105,1122,1155,1190,1309,1326,1365,
                        1430,1547,1785,1870,2002,2145,2210,2310,2431,2618,2730,2805,3003,3094,3315,3570,3927,4290,4641,4862,5005,5610,6006,6545,6630,7293,7735,7854,
                        9282,10010,12155,13090,14586,15015,15470,17017,19635,23205,24310,30030,34034,36465,39270,46410,51051,72930,85085,102102,170170,255255,510510}
        };

BOOST_FIXTURE_TEST_SUITE(test_factorisation,factoriser_fixture)

    BOOST_AUTO_TEST_CASE(test_prime_count)
    {
        BOOST_CHECK_EQUAL(F.count_primes(),78498);
    }

    BOOST_DATA_TEST_CASE(test_factorisation,dataset::make(factorisation_data)^dataset::make(factorisation_result),n,expected_primes)
    {
        auto primes=F.prime_factors(n);
        std::sort(primes.begin(),primes.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(),primes.end(),expected_primes.begin(),expected_primes.end());
    }

    BOOST_DATA_TEST_CASE(test_prime_decomposition,dataset::make(factorisation_data)^dataset::make(decomposition_result),n,expected_decomposition)
    {
        auto primes=F.prime_decomposition(10000);
        std::vector<std::pair<integer,integer>> expected_primes({{2,4},{5,4}});
        BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(),primes.end(),expected_primes.begin(),expected_primes.end());
    }


    BOOST_DATA_TEST_CASE(test_totient,dataset::make(factorisation_data)^dataset::make(totient_result),n,expected_totient)
    {
        auto totient=F.totient(n);
        BOOST_CHECK_EQUAL(totient,expected_totient);
    }

    BOOST_DATA_TEST_CASE(test_divisors,dataset::make(factorisation_data)^dataset::make(divisors_result),n,expected_divisors)
    {
        auto divisors_list=F.divisors_list(n);
        std::sort(divisors_list.begin(),divisors_list.end());
        BOOST_CHECK_EQUAL(divisors_list,expected_divisors);
    }

    /*
     * Redundant test, covered by test_divisors
     **/
    BOOST_DATA_TEST_CASE(test_divisors_count,dataset::make(factorisation_data)^dataset::make(divisors_result),n,expected_divisors)
    {
        auto divisors_count=F.divisors_count(n);
        BOOST_CHECK_EQUAL(divisors_count,expected_divisors.size());
    }

    /*
 * Redundant test, covered by test_divisors
 **/
    BOOST_DATA_TEST_CASE(test_divisors_sum,dataset::make(factorisation_data)^dataset::make(divisors_result),n,expected_divisors)
    {
        auto divisors_sum=F.divisors_sum(n);
        BOOST_CHECK_EQUAL(divisors_sum,std::reduce(expected_divisors.begin(),expected_divisors.end()));
    }

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(test_crt_suite)
BOOST_AUTO_TEST_SUITE_END()