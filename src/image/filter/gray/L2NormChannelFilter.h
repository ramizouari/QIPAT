//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_L2NORMCHANNELFILTER_H
#define IMAGEPROCESSING_L2NORMCHANNELFILTER_H

#include "GrayFilter.h"

namespace image::filter::gray {

            class L2NormChannelFilter :public GrayFilter {
                std::vector<Real> weights;
            public:
                explicit L2NormChannelFilter(const std::vector<Real> &weights);
                explicit L2NormChannelFilter(Real w1= 1, Real w2= 1, Real w3= 1);
                ~L2NormChannelFilter() override =default;
                [[nodiscard]] Image toGray(const Image& image) const override;
            };

        } // gray

#endif //IMAGEPROCESSING_L2NORMCHANNELFILTER_H
