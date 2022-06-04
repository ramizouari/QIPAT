//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_IMPULSIVENOISE_H
#define IMAGEPROCESSING_IMPULSIVENOISE_H

#include "Noise.h"
#include <random>

namespace image::noise {

        class ImpulsiveNoise :public Noise{
            Real amplitude;
            Real probability;
            std::uint64_t seed;
            std::discrete_distribution<int> distribution;
            std::mt19937_64 rng;
            public:
            explicit ImpulsiveNoise(Real probability, std::uint64_t seed);
            explicit ImpulsiveNoise(Real probability);
            ~ImpulsiveNoise() override = default;
            void apply(Image& image) override;
        };

        using SaltAndPepperNoise = ImpulsiveNoise;

    } // noise

#endif //IMAGEPROCESSING_IMPULSIVENOISE_H
