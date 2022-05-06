//
// Created by ramizouari on 02/05/22.
//

#include "GrayFilter.h"

namespace image::filter::gray {
            Image GrayFilter::apply(const Image &src) const
            {
                if(src.nb_channel==1)
                    return src;
                return toGray(src);
            }

} // gray