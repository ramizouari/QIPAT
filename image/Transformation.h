//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_TRANSFORMATION_H
#define IMAGEPROCESSING_TRANSFORMATION_H

#include "Image.h"

namespace image {

    class Transformation {
    public:
        virtual Image apply(const image::Image &image) = 0;
        virtual ~Transformation() = default;
    };

    class SelfTransformation
    {
    public:
        virtual void apply(image::Image &image) = 0;
    };

} // image

#endif //IMAGEPROCESSING_TRANSFORMATION_H
