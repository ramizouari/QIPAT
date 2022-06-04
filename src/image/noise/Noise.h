//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_NOISE_H
#define IMAGEPROCESSING_NOISE_H

#include "image/Image.h"
#include "image/Operator.h"

namespace image::noise{

        class Noise:public NonDeterministicTransformation<Image>  {
        public:
            Noise();

            ~Noise() override;

            void apply(image::Image &image) override = 0;
            void operator()(image::Image &image);
        };

    } // noise

#endif //IMAGEPROCESSING_NOISE_H
