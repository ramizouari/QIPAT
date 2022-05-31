//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_EDGEDETECTIONFILTER_H
#define IMAGEPROCESSING_EDGEDETECTIONFILTER_H

#include "image/filter/Filter.h"
#include "image/filter/gray/GrayFilter.h"
#include "image/filter/differential/DifferentialFilter.h"

namespace image::filter::edge {

class EdgeDetectionFilter :public Filter
    {
    protected:
        differential::DifferentialFilter *differentialFilter;
        gray::GrayFilter *grayFilter;
        int threshold;
    public:
        EdgeDetectionFilter(differential::DifferentialFilter *differentialFilter, gray::GrayFilter *grayFilter, int threshold);
        ~EdgeDetectionFilter() override = default ;
        [[nodiscard]] Image apply(const Image &image) const final;
        [[nodiscard]] Image apply(Padding &padding) const final;
    };

} // edge

#endif //IMAGEPROCESSING_EDGEDETECTIONFILTER_H
