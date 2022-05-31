//
// Created by ramizouari on 05/05/22.
//

#ifndef IMAGEPROCESSING_OTSUSEGMENTATION_H
#define IMAGEPROCESSING_OTSUSEGMENTATION_H

#include "image/Image.h"
#include "Segmentation.h"

namespace image::segmentation {

        class OtsuSegmentation  : public Segmentation{
        public:
            OtsuSegmentation();

            [[nodiscard]] Image apply(const image::Image &src) const;
        };

    class IterativeOtsuSegmentation :public Segmentation{
        int k;
    public:
        explicit IterativeOtsuSegmentation(int _k=2);

        [[nodiscard]] Image apply(const image::Image &src) const;
    };

    } // segmentation

#endif //IMAGEPROCESSING_OTSUSEGMENTATION_H
