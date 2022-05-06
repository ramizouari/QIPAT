//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_MEDIANFILTER_H
#define IMAGEPROCESSING_MEDIANFILTER_H

#include "Filter.h"
#include "image/Image.h"

namespace image::filter {

    class MedianFilter : public Filter {
        int size;
    public:
        explicit MedianFilter(int size);
        Image apply(const Image &src) const override;
        Image apply(const Padding &src) const override;
    };

    class SmallMedianFilter : public Filter {
        int size;
    public:
        explicit SmallMedianFilter(int size);
        Image apply(const Image &src) const override;
        Image apply(const Padding &src) const override;
    };

} // filter

#endif //IMAGEPROCESSING_MEDIANFILTER_H
