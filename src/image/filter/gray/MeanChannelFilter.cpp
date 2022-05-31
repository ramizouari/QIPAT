//
// Created by ramizouari on 02/05/22.
//

#include <numeric>
#include "MeanChannelFilter.h"

namespace image::filter::gray {
            Image MeanChannelFilter::toGray(const Image &image) const
            {
                Image dst(image.width, image.height, 1,image.max);
                for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++) for(int c=0;c<image.nb_channel;c++)
                    dst(i,j)+=weights[c]*image(c,i,j);
                return dst;
            }

    MeanChannelFilter::MeanChannelFilter(Real w1, Real w2, Real w3): weights({w1, w2, w3})
    {
        auto S=std::reduce(weights.begin(), weights.end());
        for (auto &w:this->weights)
            w/=S;
    }

    MeanChannelFilter::MeanChannelFilter(const std::vector<Real> &weights): weights(weights)
    {
        auto S=std::reduce(weights.begin(), weights.end());
        for (auto &w:this->weights)
            w/=S;
    }
} // gray