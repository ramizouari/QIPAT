//
// Created by ramizouari on 01/05/22.
//

#include "ImpulsiveNoise.h"

namespace image::noise {
        ImpulsiveNoise::ImpulsiveNoise(Real probability, std::uint64_t seed):rng(seed),probability(probability),
            distribution({static_cast<double>(probability/2),static_cast<double>(1-probability),static_cast<double>(probability/2)}) { }

        ImpulsiveNoise::ImpulsiveNoise(Real probability): ImpulsiveNoise(probability,std::random_device{}()) {}

        void ImpulsiveNoise::apply(Image &image)  {
            for(auto &C:image.data) for(auto &R:C) for(auto &v:R)
                switch(distribution(rng))
                {
                    case 0:
                        v=0;
                        break;
                    case 1:
                        continue;
                    case 2:
                        v=image.max;
                        break;
                }
        }
    } // noise