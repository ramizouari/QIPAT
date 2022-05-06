//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_ROBERTSFILTER_H
#define IMAGEPROCESSING_ROBERTSFILTER_H

#include "image/filter/differential/RobertsOperator.h"
#include "image/filter/gray/GrayFilter.h"
#include "EdgeDetectionFilter.h"

namespace image::filter::edge {

    class RobertsFilter :public EdgeDetectionFilter {
        inline static differential::RobertsOperator robertsOperator{};
    public:
        RobertsFilter(gray::GrayFilter& grayFilter,int threshold);
        ~RobertsFilter() override =default;

    };

        } // edge

#endif //IMAGEPROCESSING_ROBERTSFILTER_H
