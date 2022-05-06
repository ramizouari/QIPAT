//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_L1NORMCHANNELFILTER_H
#define IMAGEPROCESSING_L1NORMCHANNELFILTER_H

#include "GrayFilter.h"

namespace image::filter::gray {

    class L1NormChannelFilter : public GrayFilter{
        std::vector<Real> weights;
    public:
        explicit L1NormChannelFilter(const std::vector<Real> &weights);
        explicit L1NormChannelFilter(Real w1= 1, Real w2= 1, Real w3= 1);
        ~L1NormChannelFilter() override =default;
        [[nodiscard]] Image toGray(const Image& image) const override;
    };
} // gray

#endif //IMAGEPROCESSING_L1NORMCHANNELFILTER_H
