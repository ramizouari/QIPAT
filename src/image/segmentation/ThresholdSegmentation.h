//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_THRESHOLDSEGMENTATION_H
#define IMAGEPROCESSING_THRESHOLDSEGMENTATION_H

#include "Segmentation.h"

namespace image::segmentation {

    class ThresholdSegmentation : public Segmentation {
        Real threshold;
    public:
        explicit ThresholdSegmentation(Real threshold);
        ~ThresholdSegmentation() override = default;
        Image apply(const Image &image) const;

    };

} // segmentation

#endif //IMAGEPROCESSING_THRESHOLDSEGMENTATION_H
