//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_MEANBLURFILTER_H
#define IMAGEPROCESSING_MEANBLURFILTER_H

#include "ConvolutionalFilter.h"

namespace image::filter {

    class AbstractMeanBlurFilter : public AbstractConvolutionalFilter
    {
    protected:
        int size;
        inline static std::map<int,Matrix> kernels;
        static const Matrix& getKernel(int size);
    public:
        explicit AbstractMeanBlurFilter(int size);
        [[nodiscard]] const Matrix& getKernel() const override;
        [[nodiscard]] Real getComponent(int x, int y) const override;

    };

    /*
     * Optimized
     * O(width*height)
     * */
    class MeanBlurFilter : public AbstractMeanBlurFilter {
    public:
        using AbstractMeanBlurFilter::AbstractMeanBlurFilter;
        [[nodiscard]] Image apply(const Image &src) const override;
        [[nodiscard]] Image apply(Padding &src) const override;
    };

    /*
     * Naive
     * O(width*height*size)
     * */
    class SmallMeanBlurFilter : public AbstractMeanBlurFilter {
    public:
        using AbstractMeanBlurFilter::AbstractMeanBlurFilter;
        [[nodiscard]] Image apply(const Image &src) const override;
        [[nodiscard]] Image apply(Padding &src) const override;
    };

    } // filter

#endif //IMAGEPROCESSING_MEANBLURFILTER_H
