//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_NOISE_H
#define IMAGEPROCESSING_NOISE_H

#include "image/Image.h"

namespace image::noise {

        class Noise {
        public:
            Noise();

            virtual ~Noise();

            virtual void apply(image::Image &image) = 0;
            void operator()(image::Image &image);
        };

    } // noise

#endif //IMAGEPROCESSING_NOISE_H
