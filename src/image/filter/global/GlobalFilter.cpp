//
// Created by ramizouari on 04/05/22.
//

#include "GlobalFilter.h"

namespace image::filter::global {
    Image GlobalFilter::apply(Padding &src) const {
        return apply(src.image());
    }
} // Filter