//
// Created by ramizouari on 30/05/22.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mp11/list.hpp>
#include "image/Image.h"
#include "image/ImageReader.h"
#include <filesystem>
#include <fstream>
#include "image/Padding.h"
#include "image/filter/MeanBlurFilter.h"
#include "image/filter/MedianFilter.h"
#include "image/filter/GaussianBlurFilter.h"
#include "image/segmentation/OtsuSegmentation.h"

using namespace image;
constexpr Real epsilon = 1e-3;

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
    int width=30,height=50,nb_channel=n;
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

BOOST_AUTO_TEST_SUITE(image_filters)
    BOOST_AUTO_TEST_SUITE(grey_image)
        BOOST_AUTO_TEST_SUITE(blur)
            BOOST_FIXTURE_TEST_CASE(mean, sample_image_fixture<1>)
            {
                BOOST_TEST_MESSAGE("Testing mean blur filter on grey image");
                constexpr int filter_size=3;
                ZeroPadding padding(*image);
                filter::MeanBlurFilter filter(filter_size);
                Image J = filter.apply(padding);
                auto mean= [width=width,height=height](int c,int i,int j)
                {
                    Real S=0;
                    for(int k=-filter_size/2;k<=filter_size/2;k++) for(int l=-filter_size/2;l<=filter_size/2;l++)
                        S+=formula(c,i+k,j+l,width,height);
                    return S/9.;
                };
                for(int c=0;c<image->nb_channel;c++) for(int i=0;i<image->width;i++) for(int j=0;j<image->height;j++)
                    BOOST_CHECK_CLOSE(J(c,i,j),mean(c,i,j),epsilon);
            }

            BOOST_FIXTURE_TEST_CASE(median, sample_image_fixture<1>)
            {
                BOOST_TEST_MESSAGE("Testing median filter on grey image");
                constexpr int filter_size=5;
                ZeroPadding padding(*image);
                filter::MedianFilter filter(filter_size);
                Image J = filter.apply(padding);
                auto median= [width=width,height=height](int c,int i,int j)
                {
                    std::vector<Real> V;
                    V.reserve(filter_size*filter_size);
                    for(int k=-filter_size/2;k<=filter_size/2;k++) for(int l=-filter_size/2;l<=filter_size/2;l++)
                            V.push_back(formula(c,i+k,j+l,width,height));
                    std::nth_element(V.begin(),V.begin()+V.size()/2,V.end());
                    return V[V.size()/2];
                };
                for(int c=0;c<image->nb_channel;c++) for(int i=0;i<image->width;i++) for(int j=0;j<image->height;j++)
                            BOOST_CHECK_CLOSE(J(c,i,j),median(c,i,j),epsilon);
            }

            BOOST_FIXTURE_TEST_CASE(guassian, sample_image_fixture<1>)
            {
                BOOST_TEST_MESSAGE("Testing guassian blur filter on grey image");
                constexpr Real sigma=1;
                constexpr int stdcount=2;
                ZeroPadding padding(*image);
                filter::GaussianBlurFilter filter(sigma,stdcount);
                Image J = filter.apply(padding);
                auto guassian= [width=width,height=height](int c,int i,int j)
                {
                    Real S=0;
                    Real sum=0;
                    for(int k=-sigma*stdcount;k<=sigma*stdcount;k++) for(int l=-sigma*stdcount;l<=sigma*stdcount;l++)
                    {
                        Real term=std::exp(-(k*k+l*l)/(2*sigma*sigma));
                        S+=formula(c,i+k,j+l,width,height)*term;
                        sum+=term;
                    }
                    return S/sum;
                };
                for(int c=0;c<image->nb_channel;c++) for(int i=0;i<image->width;i++) for(int j=0;j<image->height;j++)
                    BOOST_CHECK_CLOSE(J(c,i,j),guassian(c,i,j),epsilon);
            }

        BOOST_AUTO_TEST_SUITE_END()

        BOOST_AUTO_TEST_SUITE(edge_detection)
        BOOST_AUTO_TEST_SUITE_END()

        BOOST_AUTO_TEST_SUITE(threshold)
            BOOST_AUTO_TEST_CASE(otsu)
            {
                BOOST_TEST_MESSAGE("Testing Otsu thresholding on grey image");
                constexpr int width=6,height=6,maximum=5,exampleThreshold=3;
                Image image({{0,0,1,4,4,5},{0,1,3,4,2,4},
                             {1,3,4,2,1,3},{4,4,3,1,0,0},
                             {5,4,2,1,0,0},{5,5,4,3,1,0}},maximum);
                segmentation::OtsuSegmentation otsu;
                Image J = otsu.apply(image);
                Image I(image);
                /*
                 *
                 * */
                for(int i=0;i<width;i++) for(int j=0;j<height;j++)
                    I(i,j) = (I(i,j)>=exampleThreshold);
                for(int i=0;i<width;i++) for(int j=0;j<height;j++)
                    BOOST_CHECK_EQUAL(J(i,j),I(i,j));
            }
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_FIXTURE_TEST_SUITE(rgb_image, sample_image_fixture<3>)
        BOOST_AUTO_TEST_SUITE(blur)
            BOOST_AUTO_TEST_CASE(mean)
            {
                BOOST_TEST_MESSAGE("Testing mean blur filter on rgb image");
                constexpr int filter_size=3;
                ZeroPadding padding(*image);
                filter::MeanBlurFilter filter(filter_size);
                Image J = filter.apply(padding);
                auto mean= [width=width,height=height](int c,int i,int j)
                {
                    Real S=0;
                    for(int k=-filter_size/2;k<=filter_size/2;k++) for(int l=-filter_size/2;l<=filter_size/2;l++)
                            S+=formula(c,i+k,j+l,width,height);
                    return S/9.;
                };
                Real error=0;
                for(int c=0;c<image->nb_channel;c++) for(int i=0;i<image->width;i++) for(int j=0;j<image->height;j++)
                            BOOST_CHECK_CLOSE(J(c,i,j),mean(c,i,j),epsilon);
            }

            BOOST_AUTO_TEST_CASE(median)
            {
                BOOST_TEST_MESSAGE("Testing median filter on rgb image");
                constexpr int filter_size=5;
                ZeroPadding padding(*image);
                filter::MedianFilter filter(filter_size);
                Image J = filter.apply(padding);
                auto median= [width=width,height=height](int c,int i,int j)
                {
                    std::vector<Real> V;
                    V.reserve(filter_size*filter_size);
                    for(int k=-filter_size/2;k<=filter_size/2;k++) for(int l=-filter_size/2;l<=filter_size/2;l++)
                            V.push_back(formula(c,i+k,j+l,width,height));
                    std::nth_element(V.begin(),V.begin()+V.size()/2,V.end());
                    return V[V.size()/2];
                };
                for(int c=0;c<image->nb_channel;c++) for(int i=0;i<image->width;i++) for(int j=0;j<image->height;j++)
                            BOOST_CHECK_CLOSE(J(c,i,j),median(c,i,j),epsilon);
            }

            BOOST_AUTO_TEST_CASE(guassian)
            {
                BOOST_TEST_MESSAGE("Testing guassian blur filter on rgb image");
                constexpr Real sigma=1;
                constexpr int stdcount=2;
                ZeroPadding padding(*image);
                filter::GaussianBlurFilter filter(sigma,sigma,stdcount);
                Image J = filter.apply(padding);
                auto guassian= [width=width,height=height](int c,int i,int j)
                {
                    Real S=0;
                    Real sum=0;
                    for(int k=-sigma*stdcount;k<=sigma*stdcount;k++) for(int l=-sigma*stdcount;l<=sigma*stdcount;l++)
                        {
                            Real term=std::exp(-(k*k+l*l)/(2*sigma*sigma));
                            S+=formula(c,i+k,j+l,width,height)*term;
                            sum+=term;
                        }
                    return S/sum;
                };
                for(int c=0;c<image->nb_channel;c++) for(int i=0;i<image->width;i++) for(int j=0;j<image->height;j++)
                            BOOST_CHECK_CLOSE(J(c,i,j),guassian(c,i,j),epsilon);
            }
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()