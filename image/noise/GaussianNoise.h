//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_GAUSSIANNOISE_H
#define IMAGEPROCESSING_GAUSSIANNOISE_H

#include <random>
#include "Noise.h"

namespace image::noise {

        class GaussianNoise : public Noise {
            double mean, stddev;
            std::normal_distribution<double> distribution;
            std::mt19937_64 rng;
        public:
            explicit GaussianNoise(double mean = 0, double stddev = 1,int seed = 0);

            void apply(image::Image &image) override;
        };

    } // noise

#endif //IMAGEPROCESSING_GAUSSIANNOISE_H
