//
// Created by ramizouari on 31/05/22.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "polynomial/polynomial.h"
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "polynomial/fft.h"
#include "nt/modular_arithmetic.h"
#include <random>
#include <chrono>
using namespace poly;
using namespace nt;
using namespace fft;
constexpr std::int64_t M = 1000000007;
constexpr int N = 100;
using IF=cyclic<M>;
constexpr double eps=1e-6;

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

namespace boost::test_tools {
    template<typename T>
    struct tt_detail::print_log_value<std::vector<T> > {
        void operator()( std::ostream& os,
                         std::vector<T> const& ts)
        {
            ::operator<<(os,ts);
        }
    };

    template<typename T>
    struct tt_detail::print_log_value<poly::polynomial<T> > {
        void operator()( std::ostream& os,
                         poly::polynomial<T> const& ts)
        {
            ::operator<<(os,ts);
        }
    };

    template<>
    struct tt_detail::print_log_value<nt::d_cyclic > {
        void operator()( std::ostream& os,
                         nt::d_cyclic const& ts)
        {
            os << (algebra::integer)ts;
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

struct factoriser_fixture
{
    inline static constexpr int LIMIT=1e6;
    inline static factoriser F{LIMIT};
    factoriser_fixture() noexcept
    {
        fft::fast_fourier<>::set_factoriser(F);
        fft::fast_fourier<>::use_normalized=true;
        fft::fast_fourier<true>::use_normalized=true;
        fft::fast_ntt<>::set_factoriser(F);
    }

    ~factoriser_fixture() noexcept
    {
        fft::fast_fourier<>::use_normalized=false;
        fft::fast_fourier<true>::use_normalized=false;
    }
};

linalg::d_matrix<IC> fourierMatrix(int n)
{
    linalg::d_matrix<IC> res(0,linalg::m_shape{n,n});
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            res[i][j]=std::exp(IC(0,2*M_PI*i*j)/static_cast<real>(n));
    return res;
}

BOOST_FIXTURE_TEST_SUITE(fft_test,factoriser_fixture)
    BOOST_AUTO_TEST_SUITE(one_dimensional)

        BOOST_AUTO_TEST_CASE(fft_result)
        {
            std::vector<IC> v={1,5,4,2};
            using namespace std::complex_literals;
            std::vector<IC> expected={12.,-3.-3.i,-2.,-3.+3.i};
            fft::fast_fourier<false> fft(v.size());
            std::vector<IC> result=fft.unnormalized(v);
            real maxDistance=0;
            for(auto [a,b]:functional::zip(result,expected))
                maxDistance=std::max(maxDistance,std::abs(a-b));
            BOOST_CHECK_LE(maxDistance,eps);
        }

        BOOST_AUTO_TEST_CASE(fft_result_normalized)
        {
            std::vector<IC> v={1,5,4,2};
            using namespace std::complex_literals;
            std::vector<IC> expected={6.,-1.5-1.5i,-1.,-1.5+1.5i};
            fft::fast_fourier<false> fft(v.size());
            std::vector<IC> result=fft.normalized(v);
            real maxDistance=0;
            for(auto [a,b]:functional::zip(result,expected))
                maxDistance=std::max(maxDistance,std::abs(a-b));
            BOOST_CHECK_LE(maxDistance,eps);
        }

        BOOST_AUTO_TEST_CASE(fft_invertible)
        {
            std::vector<IC> v={1,2,3,4,5,6,7,8,9,10};
            fft::fast_fourier<false> fft(v.size());
            fft::fast_fourier<true> ifft(v.size());
            std::vector<IC> v1=fft(v);
            std::vector<IC> v2=ifft(v1);
            real maxDistance=0;
            for(auto [a,b]:functional::zip(v,v2))
                maxDistance=std::max(maxDistance,std::abs(a-b));
            BOOST_CHECK_LE(maxDistance,eps);
        }

        BOOST_AUTO_TEST_CASE(fast_multiplication)
        {
            polynomial<IC> p1=std::vector<IC>{5,7,3,9,8,2,1,6};
            polynomial<IC> p2=std::vector<IC>{8,9,32,8,-5,8,9};
            auto expected=p1*p2;
            auto result=fft::fast_multiplication(p1,p2);
            real maxDistance=0;
            for(auto [a,b]:functional::zip(result,expected))
                BOOST_CHECK_LE(std::abs(a-b),eps);
            BOOST_CHECK_LE(maxDistance,eps);
        }

        BOOST_AUTO_TEST_CASE(fast_multiplication_speed)
        {
            BOOST_TEST_MESSAGE("Testing Fast Fourier multiplication speed");
            constexpr int N=10;
            constexpr int degree=200000;
            std::random_device dev;
            std::mt19937_64 rng(dev());
            std::uniform_int_distribution<integer> d(0,M-1);
            using namespace std::chrono_literals;

            for(int i=0;i<N;i++) {
                polynomial<IC> v1(generate_random_vector<IC>(degree+1,d,rng));
                polynomial<IC> v2(generate_random_vector<IC>(degree+1,d,rng));
                auto t1=std::chrono::high_resolution_clock::now();
                polynomial<IC> v3=fft::fast_multiplication(v1,v2);
                auto t2=std::chrono::high_resolution_clock::now();
                BOOST_CHECK(t2-t1<5s);
                BOOST_TEST_MESSAGE("Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms");
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(two_dimensional)

        BOOST_AUTO_TEST_CASE(fft_result)
        {
            std::vector<std::vector<IC>> I{{1,3,1},{5,2,0},{4,7,5},{2,5,3}};
            linalg::d_matrix<IC> expected(0,linalg::m_shape{4,3});
            auto F1=fourierMatrix(4),F2=fourierMatrix(3);
            expected=(F1*I)*F2.T()/std::sqrt(12.);
            using namespace std::complex_literals;
            std::array<int,2> dims={4,3};
            fft::multidimensional_fft<2,false> fft(dims);
            auto result=fft(I);
            real maxDistance=0;
            for(auto [A,B]:functional::zip(result,expected)) for(auto [a,b]:functional::zip(A,B))
                maxDistance=std::max(maxDistance,std::abs(a-b));
            BOOST_CHECK_LE(maxDistance,eps);
        }
        BOOST_AUTO_TEST_CASE(inversible_2D)
        {
            std::vector<std::vector<IC>> v={{1,2,3,4},{8,6,8,5},{3,9,5,2},{4,5,6,7},{5,6,7,8},{6,1,9,-5},{7,-8,3,10},{8,9,10,11},{9,10,11,12},{10,11,12,13}};
            int n=v.size(),m=v[0].size();
            std::array<int,2> dims={n,m};
            fft::multidimensional_fft<2,false> fft(dims);
            fft::multidimensional_fft<2,true> ifft(dims);
            std::vector<std::vector<IC>> v1=fft(v);
            std::vector<std::vector<IC>> v2=ifft(v1);
            real maxDistance=0;
            for(auto [A,B]:functional::zip(v,v2)) for(auto [a,b]:functional::zip(A,B))
                maxDistance=std::max(maxDistance,std::abs(a-b));
            BOOST_CHECK_LE(maxDistance,eps);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(three_dimensional)
        BOOST_AUTO_TEST_CASE(inversible_3D)
        {
            std::vector<std::vector<std::vector<IC>>> v={{{1,5,7},{2,6,9},{3,-8,7},{4,5,2}},
                                            {{2,0,4},{3,8,9},{4,4,4},{5,-2,5}},{{3,8,9},{4,2,1},{5,9,8},{6,5,4}},
                                            {{4,3,1},{5,5,5},{6,88,5},{7,10,-30}},{{5,5,1},{6,33,5},{7,0,0},{8,-5,4}},
                                            {{6,8,9},{7,3,3},{8,1,1},{9,-5,-8}},{{7,8,9},{8,7,6},{9,5,4},{10,3,2}},
                                            {{8,10,11},{9,5,1},{10,5,-5},{11,-8,-7}},{{9,-4,-2},{10,-8,-9},{11,-7,-6},{12,-4,-3}},
                                            {{10,-5,-8},{11,12,13},{12,13,14},{13,14,15}}};
            int n=v.size(),m=v[0].size(),r=v[0][0].size();
            std::array<int,3> dims={n,m,r};
            fft::multidimensional_fft<3,false> fft(dims);
            fft::multidimensional_fft<3,true> ifft(dims);
            std::vector<std::vector<std::vector<IC>>> v1=fft(v);
            std::vector<std::vector<std::vector<IC>>> v2=ifft(v1);
            real maxDistance=0;
            for(auto [A,B]:functional::zip(v,v2)) for(auto [X,Y]:functional::zip(A,B)) for(auto [a,b]:functional::zip(X,Y))
                    maxDistance=std::max(maxDistance,std::abs(a-b));
            BOOST_CHECK_LE(maxDistance,eps);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ntt_test,factoriser_fixture)
    BOOST_DATA_TEST_CASE(ntt_result,dataset::make({13,17,1000000009}),n)
    {
        using IK=d_cyclic;
        IK::m=n;
        std::vector<IK> v={1,5,4,2};
        using namespace std::complex_literals;
        auto i=sqrt(IK{-1});
        if((integer)i > n/2)
            i=-i;
        std::vector<IK> expected={12,IK{-3}-3*i,-2,IK{-3}+3*i};
        fft::fast_ntt<false> ntt(v.size(),IK::m);
        std::vector<IK> result=ntt.unnormalized(v);
        real maxDistance=0;
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),expected.begin(),expected.end());
    }

    BOOST_DATA_TEST_CASE(ntt_invertible,dataset::make({13,17,1000000009}),n)
    {
        using IK=d_cyclic;
        IK::m=n;
        std::vector<IK> v={1,5,4,2};
        using namespace std::complex_literals;
        fft::fast_ntt<false> ntt(v.size(),IK::m);
        fft::fast_ntt<true> intt(v.size(),IK::m);
        std::vector<IK> result=intt.unnormalized(ntt.unnormalized(v));
        for(auto &r:result)
            r/=v.size();
        auto &expected=v;
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),expected.begin(),expected.end());
    }

    BOOST_DATA_TEST_CASE(fast_multiplication,dataset::make({97,1000033,1000000009}),n)
    {
        using IK=d_cyclic;
        IK::m=n;
        polynomial<IK> p1=std::vector<IK>{5,7,3,9,8,2,1,6};
        polynomial<IK> p2=std::vector<IK>{8,9,32,8,-5,8,9};
        auto expected=p1*p2;
        auto result=fft::fast_multiplication(p1,p2);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),expected.begin(),expected.end());

    }

    BOOST_DATA_TEST_CASE(fast_multiplication_speed,dataset::make({10019689,1000000009}),n)
    {
        using IK=d_cyclic;
        IK::m=n;
        BOOST_TEST_MESSAGE("Testing Fast Fourier multiplication speed over cyclic Fields");
        constexpr int N=10;
        constexpr int degree=100000;
        std::random_device dev;
        std::mt19937_64 rng(dev());
        std::uniform_int_distribution<integer> d(0,M-1);
        using namespace std::chrono_literals;

        for(int i=0;i<N;i++) {
            polynomial<IK> v1(generate_random_vector<IK>(degree+1,d,rng));
            polynomial<IK> v2(generate_random_vector<IK>(degree+1,d,rng));
            auto t1=std::chrono::high_resolution_clock::now();
            polynomial<IK> v3=fft::fast_multiplication(v1,v2);
            auto t2=std::chrono::high_resolution_clock::now();
            BOOST_CHECK(t2-t1<10s);
            BOOST_TEST_MESSAGE("Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms");
        }
    }
BOOST_AUTO_TEST_SUITE_END()
