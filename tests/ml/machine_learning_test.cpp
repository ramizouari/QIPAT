//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MACHINE_LEARNING_TEST
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>
#include <fstream>
#include <boost/test/data/monomorphic/generators/xrange.hpp>
#include <boost/test/data/test_case.hpp>
#include "ml/ml.h"

namespace dataset=boost::unit_test::data;
using namespac

struct iris_fixture
{
public:
    std::vector<std::vector<real>> data;
    std::vector<real> flower_class;
    std::map<std::string, int> encoder;
    iris_fixture()
    {
        std::ifstream dataset("iris.data");
        if(dataset.fail())
            throw std::runtime_error("Could not open iris.data");

        int C = 0;
        for (std::string S; std::getline(dataset, S) && S!="";)
        {
            std::stringstream stream(S);
            std::string tmp;
            real a,b,c,d;
            char* send;
            std::getline(stream, tmp, ',');
            a = std::strtold(tmp.c_str(),&send);
            std::getline(stream, tmp, ',');
            b = std::strtold(tmp.c_str(), &send);
            std::getline(stream, tmp, ',');
            c = std::strtold(tmp.c_str(), &send);
            std::getline(stream, tmp, ',');
            d = std::strtold(tmp.c_str(), &send);
            std::string R;
            std::getline(stream, R, ',');
            if (encoder.count(R))
                flower_class.push_back(encoder[R]);
            else
                flower_class.push_back(encoder[R]=C++);
            data.push_back({ a,b,c,d });
        }
    }
};

BOOST_FIXTURE_TEST_SUITE(test_ml,iris_fixture)
    BOOST_AUTO_TEST_SUITE(iris_dataset)
        BOOST_DATA_TEST_CASE(multinomial_regression,dataset::xrange(0,100,10),C)
        {
            d_matrix<real> X(data);
            d_vector<real> y(flower_class);
            multilogistic_regression M(C);
            if(C<30)
                BOOST_CHECK_GE (M.fit(X, y).score(X,y),0.8);
            else
                BOOST_WARN_GE(M.fit(X, y).score(X,y),0.8);
            BOOST_TEST_MESSAGE("Score: " << M.score(X,y));
        }

        using K_types=boost::mp11::mp_list_c<int,1,2,3,5,10,20,100,150>;
        using norm_types=boost::mp11::mp_list<
            L2_inner_product<real,d_vector<real>>,
            L1_norm<d_vector<real>>,
            L_inf_norm<d_vector<real>>>;
        using KNN_types=boost::mp11::mp_product<std::tuple,K_types,norm_types>;
        BOOST_AUTO_TEST_CASE_TEMPLATE(knearest_neighbours,A,KNN_types)
        {
            using K_t=typename std::tuple_element_t<0,A>::type;
            using Norm=typename std::tuple_element<1,A>::type;
            d_matrix<real> X(data);
            d_vector<real> y(flower_class);
            k_nearest_neighbour_classifier<Norm> K(K_t::value);
            BOOST_CHECK_GE (K.fit(X, y).score(X,y),0.8);
            BOOST_TEST_MESSAGE("Score: " << K.score(X,y));
        }
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


