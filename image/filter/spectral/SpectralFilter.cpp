//
// Created by ramizouari on 05/05/22.
//

#include "SpectralFilter.h"
#include "image/utils.h"

namespace image::filter::spectral {

    SpectralFilter::SpectralFilter(const Matrix &kernel):kernel(kernel) {

    }

    SpectralFilter::SpectralFilter(const tensor<2> &kernel) :kernel(kernel){

    }

    Real SpectralFilter::frequencyComponent(int i, int j) const {
        return i<kernel.row_dim() && j<kernel.col_dim()? kernel[i][j]:0;
    }

    image::Image AbstractSpectralFilter::apply(const Image &image) const {
        auto M = image::generateMatrix(image.width,image.height,std::bind(&AbstractSpectralFilter::frequencyComponent,this,std::placeholders::_1,std::placeholders::_2));
        auto Z=image::convolution::fast_convolution(image,M);
        for(auto &C:Z.data) for(auto &R:C) for(auto &P:R) P=std::clamp<Real>(P/(M.col_dim()*M.row_dim()),0,image.max);
        return Z;
    }

    image::Image AbstractSpectralFilter::apply(Padding &src) const {
        return apply(src.image());
    }
} // spectral