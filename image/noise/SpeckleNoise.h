//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_SPECKLENOISE_H
#define IMAGEPROCESSING_SPECKLENOISE_H

#include "Noise.h"
#include <random>

namespace image::noise {

        class SpeckleNoise :public Noise
        {
            double stddev;
            std::normal_distribution<double> distribution;
            std::mt19937_64 rng;
        public:
            explicit SpeckleNoise(double stddev = 1,int seed = 0);

            ~SpeckleNoise() override = default;

            void apply(Image &image)  override;
        };

    } // noise

#endif //IMAGEPROCESSING_SPECKLENOISE_H
