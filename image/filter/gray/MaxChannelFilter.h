//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_MAXCHANNELFILTER_H
#define IMAGEPROCESSING_MAXCHANNELFILTER_H

#include "GrayFilter.h"

namespace image::filter::gray {

            class MaxChannelFilter:public GrayFilter {
            protected:
                [[nodiscard]] Image toGray(const Image &image) const override;
            };

        } // gray

#endif //IMAGEPROCESSING_MAXCHANNELFILTER_H
