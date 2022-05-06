//
// Created by ramizouari on 04/05/22.
//

#include "IntensityFilter.h"

namespace image::filter::global
{
    image::Image IntensityFilter::apply(const Image &image) const
    {
        Image dst(image);
        for(auto &C : dst.data) for(auto &R:C) for(auto &P: R)
            P = map(P);
        return dst;
    }
} // global