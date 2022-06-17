//
// Created by ramizouari on 30/04/22.
//
#include <numeric>
#include "stats.h"
#include <algorithm>


namespace image::stats
{
    std::vector<Stats> calculateStatistics(const Image& image)
    {
        std::vector<Stats> stats;
        for(auto &C:image.data)
        {
            stats.push_back({0,0,0,0,0});
            std::vector<Real> values;
            values.reserve(image.width*image.height);
            for(auto &R:C) for(auto &v:R)
                {
                    values.push_back(v);
                    stats.back().min=std::min(stats.back().min,v);
                    stats.back().max=std::max(stats.back().max,v);
                    stats.back().mean+=v;
                }
            stats.back().mean/=values.size();
            for(auto &R:C) for(auto &v:R)
                    stats.back().std+=std::pow(v-stats.back().mean,2);
            stats.back().std/=values.size();
            stats.back().std=std::sqrt(stats.back().std);
            std::nth_element(values.begin(),values.begin()+values.size()/2,values.end());  // median
            stats.back().median=values[values.size()/2];
        }
        return stats;
    }

    std::vector<Stats> calculateStatistics(const tensor<3>& image)
    {
        std::vector<Stats> stats;
        for(auto &C:image)
        {
            stats.push_back({0,0,0,0,0});
            std::vector<Real> values;
            values.reserve(image.size()*image.front().size());
            for(auto &R:C) for(auto &v:R)
                {
                    values.push_back(v);
                    stats.back().min=std::min(stats.back().min,v);
                    stats.back().max=std::max(stats.back().max,v);
                    stats.back().mean+=v;
                }
            stats.back().mean/=values.size();
            for(auto &R:C) for(auto &v:R)
                    stats.back().std+=std::pow(v-stats.back().mean,2);
            stats.back().std/=values.size();
            stats.back().std=std::sqrt(stats.back().std);
            std::sort(values.begin(),values.end());
            stats.back().median=values[values.size()/2];
        }
        return stats;
    }

    Stats calculateStatistics(const tensor<2>& image)
    {
        Stats stats{0,0,0,0,0};
        std::vector<Real> values;
        values.reserve(image.size()*image.front().size());
        for(auto &R:image) for(auto &v:R)
            {
                values.push_back(v);
                stats.min=std::min(stats.min,v);
                stats.max=std::max(stats.max,v);
                stats.mean+=v;
            }
        stats.mean/=values.size();
        for(auto &R:image) for(auto &v:R)
                stats.std+=std::pow(v-stats.mean,2);
        stats.std/=values.size();
        stats.std=std::sqrt(stats.std);
        std::sort(values.begin(),values.end());
        stats.median=values[values.size()/2];
        return stats;
    }

    std::vector<std::vector<Real>> histogram(const Image& image,bool normalized)
    {
        std::vector<std::vector<Real>> hist;
        hist.reserve(image.nb_channel);
        for(auto &C:image.data)
        {
            hist.emplace_back(image.max+1,0);
            for (auto &R: C)
                for (auto &v: R)
                    hist.back()[static_cast<unsigned long long>(v)]++;

            if(normalized) {
                auto S=std::reduce(hist.back().begin(),hist.back().end());
                for (auto &v: hist.back()) v /= S;
            }
        }
        return hist;
    }

    std::vector<Real> histogram(const MonoImage& image, bool normalized)
    {
        std::vector<Real> hist;
        hist.resize(image.max+1,0);
        for (auto &R: image.data.front())
            for (auto &v: R)
                hist[static_cast<unsigned int>(v)]++;
        if(normalized) {
            auto S=std::reduce(hist.begin(),hist.end());
            for (auto &v: hist) v /= S;
        }
        return hist;
    }

    Real signalToNoiseRatio(const Image &image, const Image &mask) {
        auto [_1,_2,mean,_4,_5]=calculateStatistics(image).front();
        Real S=0,N=0;
        for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++)
        {
                N += std::pow(image(i, j) - mask(i, j), 2);
                S += std::pow(image(i, j) - mean, 2);
        }
        return S/N;
    }

    std::vector<std::vector<Real>> cumulativeHistogram(const Image &image,bool normalized) {
        auto hists=histogram(image,normalized);
        for(auto &H:hists)for(int i=1;i<H.size();i++)
            H[i]+=H[i-1];
        return hists;
    }

    /*std::vector<std::vector<Real>> stats::cumulativeHistogram(const tensor<3> &image, unsigned int bits,bool normalized) {
        auto hists=histogram(image,bits,normalized);
        for(auto &H:hists)for(int i=1;i<H.size();i++)
                H[i]+=H[i-1];
        return hists;
    }*/

    /*std::vector<Real> stats::cumulativeHistogram(const MonoImage &image,bool normalized) {
        auto H=histogram(image,normalized);
        for(int i=1;i<H.size();i++)
                H[i]+=H[i-1];
        return H;
    }*/

    /*std::vector<Real> stats::cumulativeHistogram(const tensor<2> &image, unsigned int bits,bool normalized) {
        auto H=histogram(image,bits,normalized);
        for(int i=1;i<H.size();i++)
            H[i]+=H[i-1];
        return H;
    }*/
}