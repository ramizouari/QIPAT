//
// Created by ramizouari on 02/05/22.
//

#include "MaxChannelFilter.h"

namespace image::filter::gray {
            Image MaxChannelFilter::toGray(const Image &image) const {
                Image dst(image.width,image.height,1,image.max);
                for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++)
                {
                    Real S=0;
                    for(auto c=0;c<image.nb_channel;c++)
                        S=std::max(S,image(c,i,j));
                    dst(i,j)=S;
                }
                return dst;
            }
        } // gray