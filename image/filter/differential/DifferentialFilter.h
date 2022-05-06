//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_DIFFERENTIALFILTER_H
#define IMAGEPROCESSING_DIFFERENTIALFILTER_H

#include "image/filter/Filter.h"

namespace image::filter::differential {

            class DifferentialFilter :virtual public Filter {
            public:
                [[nodiscard]] Image gradientNorm(const Image &src) const;
                [[nodiscard]] Image gradientNorm(const Padding &src) const;
            };

        } // differential

#endif //IMAGEPROCESSING_DIFFERENTIALFILTER_H
