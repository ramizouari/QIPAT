//
// Created by ramizouari on 02/05/22.
//

#include <memory>
#include <numeric>
#include "ConvolutionalFilter.h"
#include <execution>
#include <future>
#include "utility.h"

namespace image::filter {
    ConvolutionalFilter::ConvolutionalFilter(const tensor<2> &kernel) :kernel(kernel) {

    }

    ConvolutionalFilter::ConvolutionalFilter(const Matrix& kernel):kernel(std::move(kernel)) {
    }

    Image ConvolutionalFilter::apply(Padding &src) const {
        Image dst(src.image().width,src.image().height,src.image().nb_channel,src.image().max);
        int s1=kernel.row_dim()/2,s2=kernel.col_dim()/2;
        for(int c=0;c<src.image().nb_channel;c++) {
            std::vector<std::future<void>> futures;

            for (int i = 0; i < src.image().width; i++) {
                futures.emplace_back(std::async([&, c, i] {
                    for (int j = 0; j < src.image().height; j++) {
                        Real sum = 0;
                        for (int p = 0; p < kernel.row_dim(); p++)
                            for (int q = 0; q < kernel.col_dim(); q++)
                                sum += kernel[p][q] * src(c, i + p - s1, j + q - s2);
                        dst(c, i, j) = std::clamp<image::Real>(sum, 0, dst.max);
                    }
                    }));
            }
        }
        return dst;
    }

    const Matrix &ConvolutionalFilter::getKernel() const {
        return kernel;
    }

    [[deprecated("Not defined")]]
    Image ConvolutionalFilter::apply(const Image &src) const {
        return Image(0, 0);
    }

    Real ConvolutionalFilter::getComponent(int x, int y) const {
        return kernel[x][y];
    }

    ConvolutionalFilter::ConvolutionalFilter(Matrix &&kernel) noexcept:kernel(std::move(kernel)) {}

    SeparableConvolutionalFilter::SeparableConvolutionalFilter(const std::vector<Real> &K1,const std::vector<Real> &K2) : K1(K1),K2(K2) {}

    SeparableConvolutionalFilter::SeparableConvolutionalFilter(const Vector& K1,const Vector& K2):K1(K1),K2(K2) {}

    const Matrix &SeparableConvolutionalFilter::getKernel() const
    {
        if(kernel)
            return *kernel;
        kernel = std::make_unique<Matrix>(0,linalg::m_shape{(int)K1.dim(),(int)K2.dim()});
        for(int i=0;i<K1.dim();i++)
            for(int j=0;j<K2.dim();j++)
                (*kernel)[i][j]=K1[i]*K2[j];
        return *kernel;
    }

    SeparableConvolutionalFilter::SeparableConvolutionalFilter(Vector &&K1, Vector &&K2) noexcept:K1(std::move(K1)),K2(std::move(K2)) {}


    Real SeparableConvolutionalFilter::getComponent(int x, int y) const {
        return K1[x]*K2[y];
    }

    Image SeparableConvolutionalFilter::apply(Padding &src) const {
        auto& orgImage=src.image();
        auto middle=applyVertical(src);
        src.setImage(middle);
        auto result=applyHorizontal(src);
        src.setImage(orgImage);
        return result;
    }

    Image SeparableConvolutionalFilter::apply(const Image &src) const {
        throw std::runtime_error("Not defined");
    }


    Image
    SeparableConvolutionalFilter::apply(const Image &src, SeparableConvolutionalFilter::Direction &direction) const {
        if(direction==Direction::HORIZONTAL)
            return applyHorizontal(src);
        else
            return applyVertical(src);
    }

    Image SeparableConvolutionalFilter::apply(const Padding &src, SeparableConvolutionalFilter::Direction &direction) const {
        if(direction==Direction::HORIZONTAL)
            return applyHorizontal(src);
        else
            return applyVertical(src);
    }

    Image SeparableConvolutionalFilter::applyHorizontal(const Padding &src) const
    {
        unsigned int L=src.image().width/utility::SOFT_CONCURRENCY_LIMIT;
        int s1=K1.dim()/2;
        Image dst(src.image().width,src.image().height,src.image().nb_channel,src.image().max);
        std::vector<std::future<void>> futures;
        for(int c=0;c<src.image().nb_channel;c++) for(int p=0;p<utility::SOFT_CONCURRENCY_LIMIT+1; p++) {
                futures.emplace_back(std::async([&, c, p] {
                    for (int q = 0, i=L*p+q; q < (p==utility::SOFT_CONCURRENCY_LIMIT?src.image().width%utility::SOFT_CONCURRENCY_LIMIT:L); q++,i++)
                        for (int j = 0; j < src.image().height; j++) for(int k=0;k<K1.dim();k++)
                                dst(c, i, j) += src(c,i, j+ k-s1) * K1[k];
                }));
            }

        return dst;
    }

    Image SeparableConvolutionalFilter::applyVertical(const Padding &src) const
    {
        unsigned int L=src.image().width/utility::SOFT_CONCURRENCY_LIMIT;
        int s2=K2.dim()/2;
        Image dst(src.image().width,src.image().height,src.image().nb_channel,src.image().max);
        std::vector<std::future<void>> futures;
        for(int c=0;c<src.image().nb_channel;c++) for(int p=0;p<utility::SOFT_CONCURRENCY_LIMIT+1; p++) {
                futures.emplace_back(std::async([&, c, p] {
                    for (int q = 0,i=L*p+q; q<(p==utility::SOFT_CONCURRENCY_LIMIT?src.image().width%utility::SOFT_CONCURRENCY_LIMIT:L); q++,i++)
                        for (int j = 0; j < src.image().height; j++) for(int k=0;k<K2.dim();k++)
                                dst(c, i, j) += src(c, i+k-s2, j) * K2[k];
                }));
            }
        return dst;
    }

    Image SeparableConvolutionalFilter::applyHorizontal(const Image &src) const {
        return Image(0, 0);
    }

    Image SeparableConvolutionalFilter::applyVertical(const Image &src) const {
        return Image(0, 0);
    }


} // filter