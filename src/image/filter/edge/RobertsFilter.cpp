//
// Created by ramizouari on 03/05/22.
//

#include "RobertsFilter.h"

namespace image::filter::edge {
            RobertsFilter::RobertsFilter(gray::GrayFilter &grayFilter, int threshold): EdgeDetectionFilter(&robertsOperator,&grayFilter,threshold) {}
        } // edge