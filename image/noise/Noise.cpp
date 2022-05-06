//
// Created by ramizouari on 01/05/22.
//

#include "Noise.h"

namespace image {
    namespace noise {
        void Noise::operator()(Image &image) {
            apply(image);
        }

        Noise::Noise() {

        }

        Noise::~Noise() {

        }
    } // image
} // noise