//
// Created by ramizouari on 01/05/22.
//

#include "GaussianNoise.h"

namespace image::noise {
        GaussianNoise::GaussianNoise(double mean, double stddev,int seed):
                mean(mean), stddev(stddev),rng(seed),distribution(mean,stddev) {}

    void GaussianNoise::apply(Image &image) {
        for(auto &C:image.data) for(auto &R:C) for(auto &v:R)
            v = std::clamp<Real>(v+distribution(rng),0.0,image.max);
    }

} // noise