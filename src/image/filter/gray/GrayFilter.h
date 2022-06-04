//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_GRAYFILTER_H
#define IMAGEPROCESSING_GRAYFILTER_H

#include "image/filter/Filter.h"
#include "image/filter/global/GlobalFilter.h"

namespace image::filter::gray {

class GrayFilter:public global::GlobalFilter {
            protected:
                [[nodiscard]] virtual Image toGray(const Image& src) const =0;
            public:
                [[nodiscard]] Image apply(const Image& src) const final;
            };

        } // gray

#endif //IMAGEPROCESSING_GRAYFILTER_H
