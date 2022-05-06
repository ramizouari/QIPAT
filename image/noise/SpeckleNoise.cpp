//
// Created by ramizouari on 06/05/22.
//

#include "SpeckleNoise.h"

namespace image::noise {
    SpeckleNoise::SpeckleNoise(double stddev, int seed) : stddev(stddev),rng(seed),distribution(1,stddev){

    }

    void SpeckleNoise::apply(Image &image) {
        for(auto &C:image.data) for(auto &R:C) for(auto &v:R)
                    v = std::clamp<Real>(v*distribution(rng),0.0,image.max);
    }
} // noise