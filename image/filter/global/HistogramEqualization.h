//
// Created by ramizouari on 04/05/22.
//

#ifndef IMAGEPROCESSING_HISTOGRAMEQUALIZATION_H
#define IMAGEPROCESSING_HISTOGRAMEQUALIZATION_H

#include "IntensityFilter.h"

namespace image::filter::global {

    class HistogramEqualization :public GlobalFilter
    {
    public:
        HistogramEqualization() = default;
        ~HistogramEqualization() override = default;
        Image apply(const Image &image) const override;
    };

        } // global

#endif //IMAGEPROCESSING_HISTOGRAMEQUALIZATION_H
