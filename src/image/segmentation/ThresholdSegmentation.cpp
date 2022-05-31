//
// Created by ramizouari on 06/05/22.
//

#include "ThresholdSegmentation.h"
#include "functional/functional.h"
#include "functional/zip.h"

namespace image::segmentation {
        Image ThresholdSegmentation::apply(const Image &image) const
        {
              Image dst(image.width, image.height, image.nb_channel,1);
              for(auto [A,B]: functional::zip(image.data, dst.data)) for(auto [X,Y]: functional::zip(A,B)) for(auto [x,y]: functional::zip(X,Y))
                  y = x > threshold ? 1 : 0;
              return dst;
        }

    ThresholdSegmentation::ThresholdSegmentation(Real threshold):threshold(threshold) {}
} // segmentation