//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_LAPLACIANFILTER_H
#define IMAGEPROCESSING_LAPLACIANFILTER_H

#include "image/filter/ConvolutionalFilter.h"
#include "EdgeDetectionFilter.h"
#include "image/filter/differential/LaplacianOperator.h"

namespace image::filter::edge {


    class LaplacianFilter : public EdgeDetectionFilter {
    public:
        inline static differential::LaplacianOperator laplacianOperator{};
        inline static differential::LaplacianOperatorWithDiagonal laplacianOperatorWithDiagonal{};
    public:
        LaplacianFilter(gray::GrayFilter& grayFilter,int threshold,bool includeDiagonal=false);
        ~LaplacianFilter() override =default;
    };


} // filter

#endif //IMAGEPROCESSING_LAPLACIANFILTER_H
