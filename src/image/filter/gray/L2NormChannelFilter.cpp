//
// Created by ramizouari on 03/05/22.
//

#include "L2NormChannelFilter.h"

namespace image::filter::gray
{
    Image L2NormChannelFilter::toGray(const Image &image) const
    {
        Image dst(image.width, image.height, 1,image.max);
        for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++) for(int c=0;c<image.nb_channel;c++)
                    dst(i,j)+=weights[c]*std::pow(image(c,i,j),2);
        for(auto &R:dst.data.front()) for(auto &v:R)
                v=std::clamp<Real>(std::sqrt(v),0,image.max);
        return dst;
    }

    L2NormChannelFilter::L2NormChannelFilter(Real w1, Real w2, Real w3): weights({w1, w2, w3})
    {
    }

    L2NormChannelFilter::L2NormChannelFilter(const std::vector<Real> &weights): weights(weights)
    {
    }
} // gray