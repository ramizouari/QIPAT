//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TOPOLOGY_TEST
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>
#include <fstream>
#include <boost/test/data/monomorphic/generators/xrange.hpp>
#include <boost/test/data/test_case.hpp>
#include "topology/topology.h"
using namespace linalg;
using namespace topology;
using namespace linalg;
namespace dataset=boost::unit_test::data;
using dimensions=boost::mp11::mp_list_c<integer,1,2,3,5,10,100,1000,100000>;
using complex_dimensions=boost::mp11::mp_list_c<integer,1,2,3,5,10,100,1000,50000>;

struct points_fixture
{
};

constexpr real err=1e-6;

BOOST_AUTO_TEST_SUITE(test_norms)
    BOOST_FIXTURE_TEST_SUITE(real_norms,points_fixture)
        BOOST_AUTO_TEST_SUITE(L1)
            BOOST_AUTO_TEST_CASE_TEMPLATE(distance,dimension,dimensions)
            {
                s_vector<real,dimension::value> v1,v2;
                L1_norm<s_vector<real,dimension::value>> norm;
                for(int i=0;i<dimension::value;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),dimension::value,err);
            }
            BOOST_DATA_TEST_CASE(d_distance,dataset::make(1,2,3,10,1000,1000000,10000000),dimension)
            {
                d_vector<real> v1(v_shape{dimension}),v2(v_shape{dimension});
                L1_norm<d_vector<real>> norm;
                for(int i=0;i<dimension;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),dimension,err);
            }
        BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE(L2)
            BOOST_AUTO_TEST_CASE_TEMPLATE(distance,dimension,dimensions)
            {
                s_vector<real,dimension::value> v1,v2;
                L2_inner_product<real,s_vector<real,dimension::value>> norm;
                for(int i=0;i<dimension::value;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),std::sqrt(dimension::value),err);
            }
            BOOST_DATA_TEST_CASE(d_distance,dataset::make(1,2,3,10,1000,1000000,10000000),dimension)
            {
                d_vector<real> v1(v_shape{dimension}),v2(v_shape{dimension});
                L2_inner_product<real,d_vector<real>> norm;
                for(int i=0;i<dimension;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),std::sqrt(dimension),err);
            }

        BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE(Linf)
            BOOST_AUTO_TEST_CASE_TEMPLATE(distance,dimension,dimensions)
            {
                s_vector<real,dimension::value> v1,v2;
                L_inf_norm<s_vector<real,dimension::value>> norm;
                for(int i=0;i<dimension::value;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),1,err);
            }

            BOOST_DATA_TEST_CASE(d_distance,dataset::make(1,2,3,10,1000,1000000,10000000),dimension)
            {
                d_vector<real> v1(v_shape{dimension}),v2(v_shape{dimension});
                L_inf_norm<d_vector<real>> norm;
                for(int i=0;i<dimension;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),1,err);
            }
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_FIXTURE_TEST_SUITE(complex_norms,points_fixture)
        BOOST_AUTO_TEST_SUITE(L1)
            BOOST_AUTO_TEST_CASE_TEMPLATE(distance,dimension,complex_dimensions)
            {
                s_vector<IC,dimension::value> v1,v2;
                L1_norm<s_vector<IC,dimension::value>> norm;
                for(int i=0;i<dimension::value;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),dimension::value,err);
            }
            BOOST_DATA_TEST_CASE(d_distance,dataset::make(1,2,3,10,1000,1000000,10000000),dimension)
            {
                d_vector<IC> v1(v_shape{dimension}),v2(v_shape{dimension});
                L1_norm<d_vector<IC>> norm;
                for(int i=0;i<dimension;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),dimension,err);
            }
        BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE(L2)
            BOOST_AUTO_TEST_CASE_TEMPLATE(distance,dimension,complex_dimensions)
            {
                s_vector<IC,dimension::value> v1,v2;
                L2_inner_product<IC,s_vector<IC,dimension::value>> norm;
                for(int i=0;i<dimension::value;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),std::sqrt(dimension::value),err);
            }
            BOOST_DATA_TEST_CASE(d_distance,dataset::make(1,2,3,10,1000,1000000,10000000),dimension)
            {
                d_vector<IC> v1(v_shape{dimension}),v2(v_shape{dimension});
                L2_inner_product<IC,d_vector<IC>> norm;
                for(int i=0;i<dimension;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),std::sqrt(dimension),err);
            }

        BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE(Linf)
            BOOST_AUTO_TEST_CASE_TEMPLATE(distance,dimension,complex_dimensions)
            {
                s_vector<IC,dimension::value> v1,v2;
                L_inf_norm<s_vector<IC,dimension::value>> norm;
                for(int i=0;i<dimension::value;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),1,err);
            }

            BOOST_DATA_TEST_CASE(d_distance,dataset::make(1,2,3,10,1000,1000000,10000000),dimension)
            {
                d_vector<IC> v1(v_shape{dimension}),v2(v_shape{dimension});
                L_inf_norm<d_vector<IC>> norm;
                for(int i=0;i<dimension;++i)
                {
                    v1[i]=i;
                    v2[i]=i+1;
                }
                BOOST_CHECK_CLOSE(norm.distance(v1,v2),1,err);
            }
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_inner_products)
    BOOST_AUTO_TEST_CASE_TEMPLATE(inner_product_real,dimension,dimensions)
    {
        s_vector<real,dimension::value> v1,v2;
        L2_inner_product<real,s_vector<real,dimension::value>> norm;
        for(int i=0;i<dimension::value;++i)
        {
            v1[i]=i;
            v2[i]=i;
        }
        auto &N=dimension::value;
        BOOST_CHECK_CLOSE(norm.inner_product(v1,v2),N*(N-1)*(2*N-1)/6,err);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(inner_product_real_random,dimension,dimensions)
    {
        std::random_device dev;
        std::mt19937_64  rng(dev());
        std::uniform_real_distribution<real> d(-1e5,1e5);
        s_vector<real,dimension::value> v1,v2;
        L2_inner_product<real,s_vector<real,dimension::value>> norm;
        for(int i=0;i<dimension::value;++i)
        {
            v1[i]=d(rng);
            v2[i]=d(rng);
        }
        auto &N=dimension::value;
        auto V=std::inner_product(v1.begin(),v1.end(),v2.begin(),0.0);
        BOOST_CHECK_CLOSE(norm.inner_product(v1,v2),V,err);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(inner_product_complex,dimension,dimensions)
    {
        s_vector<IC,dimension::value> v1,v2;
        L2_inner_product<IC,s_vector<IC,dimension::value>> norm;
        using namespace std::complex_literals;
        for(int i=0;i<dimension::value;++i)
        {
            v1[i]=static_cast<real>(i)*1.Li;
            v2[i]=-v1[i];
        }
        auto &N=dimension::value;
        auto V=norm.inner_product(v1,v2);
        BOOST_CHECK_CLOSE(V.real(),-N*(N-1)*(2*N-1)/6,err);
        BOOST_CHECK_CLOSE(V.imag(),0,err);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(inner_product_complex_random,dimension,complex_dimensions)
    {
        std::random_device dev;
        std::mt19937_64  rng(dev());
        std::uniform_real_distribution<real> d(-1e5,1e5);
        s_vector<IC,dimension::value> v1,v2;
        L2_inner_product<IC,s_vector<IC,dimension::value>> norm;
        for(int i=0;i<dimension::value;++i)
        {
            v1[i]=d(rng)+1.Li*d(rng);
            v2[i]=d(rng)+1.Li*d(rng);
        }
        auto &N=dimension::value;
        auto V1=norm.inner_product(v1,v2);
        auto v3=conj(v1);
        auto V2=std::inner_product(v3.begin(),v3.end(),v2.begin(),IC{});
        BOOST_CHECK_CLOSE(V1.real(),V2.real(),err);
        BOOST_CHECK_CLOSE(V1.imag(),V2.imag(),err);
    }

BOOST_AUTO_TEST_SUITE_END()


