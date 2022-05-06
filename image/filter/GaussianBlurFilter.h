//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_GAUSSIANBLURFILTER_H
#define IMAGEPROCESSING_GAUSSIANBLURFILTER_H

#include "ConvolutionalFilter.h"

namespace image::filter {

        class GaussianBlurFilter:public SeparableConvolutionalFilter {
            Real stdX, stdY;
            int stdCount;
        public:
            GaussianBlurFilter(Real stdX,Real stdY,int stdCount=3);
            explicit GaussianBlurFilter(Real std,int stdCount=3);
            ~GaussianBlurFilter() override =default;
            static std::pair<Vector,Vector> getKernels(Real stdX,Real stdY,int stdCount=3);
        };

    } // filter

#endif //IMAGEPROCESSING_GAUSSIANBLURFILTER_H
