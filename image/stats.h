//
// Created by ramizouari on 30/04/22.
//

#ifndef IMAGEPROCESSING_STATS_H
#define IMAGEPROCESSING_STATS_H
#include "Image.h"

namespace image::stats
    {
        struct Stats
        {
            Real min;
            Real max;
            Real mean;
            Real median;
            Real std;
        };
        std::vector<Stats> calculateStatistics(const Image& image);
        std::vector<Stats> calculateStatistics(const Image& image, const Image& mask);
        Stats calculateStatistics(const tensor<2> &image);
        Stats calculateStatistics(const tensor<2> &image, const tensor<2> &mask);
        Stats calculateStatistics(const MonoImage &image);
        std::vector<Stats> calculateStatistics(const tensor<3> &image);
        std::vector<Stats> calculateStatistics(const tensor<3> &image, const tensor<3> &mask);
        std::vector<std::vector<Real>> histogram(const Image& image,bool normalized=false);
        std::vector<std::vector<Real>> histogram(const tensor<3>& image, unsigned int bits,bool normalized=false);
        std::vector<Real> histogram(const MonoImage& image, bool normalized=false);
        std::vector<Real> histogram(const tensor<2>& image, unsigned int bits,bool normalized=false);

        std::vector<std::vector<Real>> cumulativeHistogram(const Image& image,bool normalized=false);
        std::vector<std::vector<Real>> cumulativeHistogram(const tensor<3>& image, unsigned int bits,bool normalized=false);
        std::vector<Real> cumulativeHistogram(const MonoImage& image, bool normalized=false);
        std::vector<Real> cumulativeHistogram(const tensor<2>& image, unsigned int bits,bool normalized=false);

        Real signalToNoiseRatio(const Image& image, const Image& mask);

}

#endif //IMAGEPROCESSING_STATS_H
