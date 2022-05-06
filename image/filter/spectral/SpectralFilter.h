//
// Created by ramizouari on 05/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRALFILTER_H
#define IMAGEPROCESSING_SPECTRALFILTER_H

#include "image/filter/Filter.h"

namespace image::filter::spectral {

    class AbstractSpectralFilter : public Filter
    {
    public:
        [[nodiscard]] virtual Real frequencyComponent(int i, int j) const = 0;
        [[nodiscard]] image::Image apply(const image::Image &image) const override;
        [[nodiscard]] image::Image apply(const Padding &src) const override;
    };


    class SpectralFilter : public AbstractSpectralFilter
    {
        Matrix kernel;
    public:
        explicit SpectralFilter(const Matrix &kernel);
        explicit SpectralFilter(const tensor<2> &kernel);
        [[nodiscard]] Real frequencyComponent(int i, int j) const override;
    };
} // spectral

#endif //IMAGEPROCESSING_SPECTRALFILTER_H
