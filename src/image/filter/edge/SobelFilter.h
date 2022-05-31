//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_SOBELFILTER_H
#define IMAGEPROCESSING_SOBELFILTER_H

#include "image/filter/Filter.h"
#include "image/filter/ConvolutionalFilter.h"
#include "EdgeDetectionFilter.h"
#include "image/filter/differential/SobelOperator.h"

namespace image::filter::edge {

        class SobelFilter:public EdgeDetectionFilter
        {
            inline static differential::SobelOperator sobelOperator{};
        public:
            SobelFilter(gray::GrayFilter& grayFilter,int threshold);
            ~SobelFilter() override =default;
        };

}// filter

#endif //IMAGEPROCESSING_SOBELFILTER_H
