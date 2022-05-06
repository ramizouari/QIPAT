//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_CONVOLUTIONALFILTER_H
#define IMAGEPROCESSING_CONVOLUTIONALFILTER_H

#include "image/Image.h"
#include "Filter.h"
#include "image/utils.h"

namespace image::filter {

    class AbstractConvolutionalFilter : virtual public Filter {
    public:

        [[nodiscard]] virtual const Matrix &getKernel() const = 0;

        [[nodiscard]] virtual Real getComponent(int i, int j) const = 0;
    };

    class ConvolutionalFilter : public AbstractConvolutionalFilter {
        Matrix kernel;
    public:
        explicit ConvolutionalFilter(const tensor<2> &kernel);

        explicit ConvolutionalFilter(const Matrix& kernel);
        explicit ConvolutionalFilter(Matrix &&kernel) noexcept;

        [[nodiscard]] Image apply(const Image &src) const override;

        [[nodiscard]] Image apply(const Padding &src) const override;

        [[nodiscard]] const Matrix &getKernel() const override;

        [[nodiscard]] Real getComponent(int x, int y) const override;


    };

    class GeneratedConvolutionalFilter : public ConvolutionalFilter {
    public:
        template<image::RealMatrixGenerator Generator>
        explicit GeneratedConvolutionalFilter(int width, int height, const Generator &generator):
                ConvolutionalFilter(generateMatrix(width, height, generator)) {}

    }; // filter



    class SeparableConvolutionalFilter : public AbstractConvolutionalFilter
    {
        Vector K1,K2;
    public:
        explicit SeparableConvolutionalFilter(const std::vector<Real> &K1,const std::vector<Real> &K2);

        explicit SeparableConvolutionalFilter(const Vector &K1,const Vector& K2);
        explicit SeparableConvolutionalFilter(Vector &&K1,Vector &&K2) noexcept;

        [[nodiscard]] Image apply(const Image &src) const override;

        [[nodiscard]] Image apply(const Padding &src) const override;

        [[nodiscard]] const Matrix &getKernel() const override;

        [[nodiscard]] Real getComponent(int x, int y) const override;


    };

}
#endif //IMAGEPROCESSING_CONVOLUTIONALFILTER_H
