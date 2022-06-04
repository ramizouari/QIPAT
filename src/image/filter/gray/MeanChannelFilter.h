//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_MEANCHANNELFILTER_H
#define IMAGEPROCESSING_MEANCHANNELFILTER_H

#include "GrayFilter.h"

namespace image::filter::gray {

            class MeanChannelFilter : public GrayFilter{
                std::vector<Real> weights;
            public:
                explicit MeanChannelFilter(const std::vector<Real> &weights);
                explicit MeanChannelFilter(Real w1= 1.L / 3, Real w2= 1.L / 3, Real w3= 1.L / 3);
                ~MeanChannelFilter() override =default;
                [[nodiscard]] Image toGray(const Image& image) const override;
            };
        } // gray

#endif //IMAGEPROCESSING_MEANCHANNELFILTER_H
