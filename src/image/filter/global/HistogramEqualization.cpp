//
// Created by ramizouari on 04/05/22.
//

#include "HistogramEqualization.h"
#include "image/utils.h"

namespace image::filter::global {
            Image HistogramEqualization::apply(const Image &image) const {
                return image::histogramEqualization(image);
            }
        } // global