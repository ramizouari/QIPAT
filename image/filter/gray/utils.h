//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_GRAY_UTILS_H
#define IMAGEPROCESSING_GRAY_UTILS_H

#include "GrayFilter.h"

namespace image::filter::gray
{
    extern GrayFilter &maxChannelFilter;
    extern GrayFilter &meanChannelFilter;
    extern GrayFilter &rec709Filter;
    extern GrayFilter &rec601Filter;
    extern GrayFilter &l1NormFilter;
    extern GrayFilter &l2NormFilter;
}
#endif //IMAGEPROCESSING_GRAY_UTILS_H
