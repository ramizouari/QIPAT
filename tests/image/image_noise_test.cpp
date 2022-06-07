//
// Created by ramizouari on 31/05/22.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mp11/list.hpp>
#include "image/Image.h"
#include <filesystem>
#include <fstream>
#include "image/Padding.h"
#include "image/filter/MeanBlurFilter.h"
#include "image/filter/MedianFilter.h"
#include "image/filter/GaussianBlurFilter.h"
#include "image/segmentation/OtsuSegmentation.h"
#include "image/noise/GaussianNoise.h"
#include "image/noise/ImpulsiveNoise.h"
#include "image/noise/SpeckleNoise.h"
#include <boost/math/special_functions/gamma.hpp>
#include <numbers>


using namespace image;
constexpr Real likelihoodLimit = 1e-6;
constexpr Real eps=1e-6;

inline Real formula(int c,int i,int j,int width,int height)
{
    if(i>= 0 && i < width && j >= 0 && j < height)
        return (c*height*width+i*width+j+1);
    else
        return 0;
}

inline Real formula(int i,int j)
{
    return i*30+j;
}

template<int n>
struct sample_image_fixture
{
    std::unique_ptr<Image> image;
    int width=10,height=10,nb_channel=n;
    sample_image_fixture()
    {
        image = std::make_unique<Image>(width,height,nb_channel);
        for(int i=0;i<width;i++) for(int j=0;j<height;j++) for(int c=0;c<nb_channel;c++)
                    (*image)(c,i,j) = formula(c,i,j,width,height);
    }

};

struct binary_image_fixture
{
    std::unique_ptr<Image> image;
    int width=30,height=50;
    binary_image_fixture()
    {
        image = std::make_unique<Image>(width,height,1);
        for(int i=0;i<width;i++) for(int j=0;j<height;j++) (*image)(0,i,j) = (i+j)%2;
    }

};

Real RadiusUpperBound(int n, Real p, Real eps)
{
    Real beta=0,alpha=0,n2=n/2.;
    while(boost::math::gamma_p(n2, n2 + beta) - boost::math::gamma_p(n2, std::max<Real>(n2 - beta,0)) < p) beta=2*beta+eps;
    Real c=0;
    while(beta-alpha > eps)
    {
        c=(beta+alpha)/2;
        auto R=boost::math::gamma_p(n2, n2 + c),L=boost::math::gamma_p(n2, std::max<Real>(n2 - c,0));
        if(R - L < p)
            alpha=c;
        else
            beta=c;
    }
    return 2*beta;
}


Real probit(Real p)
{
    return std::numbers::sqrt2 * boost::math::erf_inv(2*p-1);
}

std::pair<Real,Real> wilsonScoreInterval(int n,int sucess,Real confidence)
{
    Real p=sucess/(Real)n,z=probit(confidence),z2=z*z,
        center=(sucess+z2/2)/(z2+n),radius=z/(z2+n)*std::sqrt(p*(n-sucess)+z2/4);
    return std::make_pair(center-radius,center+radius);
}

BOOST_AUTO_TEST_SUITE(image_noise)
    BOOST_AUTO_TEST_SUITE(grey_image)
    /*
     * Unit Test for Gaussian Noise on grey image
     * Theoretical Justification is given on the report
     * */
            BOOST_FIXTURE_TEST_CASE(gaussian, sample_image_fixture<1>)
            {
                //Given
                constexpr double std=15;
                BOOST_TEST_MESSAGE("Gaussian noise test on grey image, with std=" << std << " and eps=" << eps);
                image::noise::GaussianNoise noise(0,std,0);
                auto &I= *image;
                I.max=1e6;
                auto J=I;
                Real Xi=0;

                //When
                noise.apply(J);
                for(int i=0;i<width;i++) for(int j=0;j<height;j++) for(int c=0;c<nb_channel;c++)
                {
                    Real diff=J(c,i,j)-I(c,i,j);
                    Xi+=diff*diff;
                }
                Xi/=std*std;
                auto n=width*height*nb_channel;
                auto r= RadiusUpperBound(n, 1 - likelihoodLimit, eps);
                Real XiLower= n-r, XiUpper=n+r;

                //Expected
                if(Xi > XiLower && Xi < XiUpper)
                    BOOST_CHECK_MESSAGE(true,"Difference is consistent with the desired gaussian distribution");
                else
                    BOOST_CHECK_MESSAGE(false,"Difference is not consistent with the desired gaussian distribution");

            }
/*
 * Unit Test for Impulsive Noise on grey image
 * Based on Wilson's test
 * */
        BOOST_FIXTURE_TEST_CASE(impulse, sample_image_fixture<1>)
        {
                //Given
            constexpr double p=0.1;
            auto &I= *image;
            I.max=1e6;
            BOOST_TEST_MESSAGE("Impulse noise test on grey image, with p=" << p << " and eps=" << eps);
            image::noise::ImpulsiveNoise noise(0.1);
            int impulseCount=0;

            //When
            noise.apply(I);
            for(int c=0;c<nb_channel;c++) for(int i=0;i<width;i++) for(int j=0;j<height;j++) if(I(c,i,j)==0 || I(c,i,j)==I.max)
                impulseCount++;
            auto [L,R] = wilsonScoreInterval(width*height*nb_channel,impulseCount,1-likelihoodLimit);
            //Expected
            if(p > L && p < R)
                BOOST_CHECK_MESSAGE(true,"Impulses are consistent with the desired binomial distribution");
            else
                BOOST_CHECK_MESSAGE(false,"Impulses are not consistent with the desired binomial distribution");
        }
        /*
         * Unit Test for Speckle Noise on grey image
         * Theoretical Justification is given on the report
         * */
        BOOST_FIXTURE_TEST_CASE(speckle, sample_image_fixture<1>)
        {
            //Given
            constexpr double std=0.4;
            image::noise::SpeckleNoise noise(std);
            auto &I= *image;
            I.max=1e6;
            BOOST_TEST_MESSAGE("Speckle noise test, with std=" << std << " and eps=" << eps);
            auto J=I;
            Real Xi=0;
            int n=0;
            //When
            noise.apply(J);

            for(int i=0;i<width;i++) for(int j=0;j<height;j++) for(int c=0;c<nb_channel;c++) if(I(c,i,j) > 0 && J(c,i,j) < I.max)
            {
                n++;
                Real ratio=J(c,i,j)/I(c,i,j);
                Xi+=(ratio-1)*(ratio-1);
            }
            Xi/=std*std;
            auto r= RadiusUpperBound(n, 1 - likelihoodLimit, eps);
            Real XiLower= n-r, XiUpper=n+r;
            //Expect
            if(Xi > XiLower && Xi < XiUpper)
                BOOST_CHECK_MESSAGE(true,"Ratio is consistent with the desired gaussian distribution");
            else
                BOOST_CHECK_MESSAGE(false,"Ratio is not consistent with the desired gaussian distribution");

        }

    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(rgb_image)

    /* Unit test for Gaussian Noise on RGB image
     * Theoretical Justification is given on the report
     * */
        BOOST_FIXTURE_TEST_CASE(gaussian, sample_image_fixture<1>)
        {
            constexpr double std=15;
            constexpr int stdCount=10;
            BOOST_TEST_MESSAGE("Gaussian noise test on rgb image, with std=" << std << " and eps=" << eps);
            image::noise::GaussianNoise noise(0,std,0);
            auto &I= *image;
            I.max=1e6;
            auto J=I;
            noise.apply(J);
            Real Xi=0;
            for(int i=0;i<width;i++) for(int j=0;j<height;j++) for(int c=0;c<nb_channel;c++)
            {
                Real diff=J(c,i,j)-I(c,i,j);
                Xi+=diff*diff;
            }
            Xi/=std*std;
            auto n=width*height*nb_channel;
            auto r= RadiusUpperBound(n, 1 - likelihoodLimit, eps);
            Real XiLower= n-r, XiUpper=n+r;
            if(Xi > XiLower && Xi < XiUpper)
                BOOST_CHECK_MESSAGE(true,"Difference is consistent with the desired gaussian distribution");
            else
                BOOST_CHECK_MESSAGE(false,"Difference is not consistent with the desired gaussian distribution");

        }

        /* Unit test for Impulsive Noise on RGB image
         * Based on Wilson's test
         * */
        BOOST_FIXTURE_TEST_CASE(impulse, sample_image_fixture<3>)
        {
            constexpr double p=0.1;
            auto &I= *image;
            I.max=1e6;
            image::noise::ImpulsiveNoise noise(0.1);
            int impulseCount=0;
            noise.apply(I);
            for(int c=0;c<nb_channel;c++) for(int i=0;i<width;i++) for(int j=0;j<height;j++) if(I(c,i,j)==0 || I(c,i,j)==I.max)
                impulseCount++;
            auto [L,R] = wilsonScoreInterval(width*height*nb_channel,impulseCount,1-likelihoodLimit);
            if(p > L && p < R)
                BOOST_CHECK_MESSAGE(true,"Impulses are consistent with the desired binomial distribution");
            else
                BOOST_CHECK_MESSAGE(false,"Impulses are not consistent with the desired binomial distribution");
        }

        /* Unit test for Speckle Noise on RGB image
         * Theoretical Justification is given on the report
         * */

        BOOST_FIXTURE_TEST_CASE(speckle, sample_image_fixture<3>)
        {
            constexpr double std=0.4;
            image::noise::SpeckleNoise noise(std);
            auto &I= *image;
            I.max=1e6;
            auto J=I;
            noise.apply(J);
            Real Xi=0;
            int n=0;
            for(int i=0;i<width;i++) for(int j=0;j<height;j++) for(int c=0;c<nb_channel;c++) if(I(c,i,j) > 0 && J(c,i,j) < I.max)
            {
                n++;
                Real ratio=J(c,i,j)/I(c,i,j);
                Xi+=(ratio-1)*(ratio-1);
            }
            Xi/=std*std;
            auto r= RadiusUpperBound(n, 1 - likelihoodLimit, eps);
            Real XiLower= n-r, XiUpper=n+r;
            if(Xi > XiLower && Xi < XiUpper)
                BOOST_CHECK_MESSAGE(true,"Ratio is consistent with the desired gaussian distribution");
            else
                BOOST_CHECK_MESSAGE(false,"Ratio is not consistent with the desired gaussian distribution");

        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()