//
// Created by ramizouari on 04/05/22.
//

#include "IntensityMapper.h"

namespace image::filter::global {
            Real IntensityMapper::map(Real c) const {
                return mapper[static_cast<int>(c)];
            }

    IntensityMapper::IntensityMapper(const std::vector<Real> &mapper):mapper(mapper) {}

    IntensityMapper::IntensityMapper(std::vector<Real> &&mapper):mapper(std::move(mapper)) {}

    IntensityMapper::IntensityMapper(std::vector<std::pair<Real, Real>> points) {
        std::sort(points.begin(), points.end());
        int maxValue = points.back().first,n=points.size();
        mapper.resize(maxValue+1);
        for(int i=0;i<n-1;i++)
        {
            Real alpha=(points[i+1].second-points[i].second)/(points[i+1].first-points[i].first);
            for(int k=points[i].first;k<points[i+1].first;k++)
                mapper[k]=alpha*(k-points[i].first)+points[i].second;
        }
        mapper[points.back().first]=points.back().second;
    }

    IntensityMapper::IntensityMapper(std::vector<Vector2> points)
    {
        std::sort(points.begin(), points.end(),[](const auto &x, const auto &y) {
            return x[0] < y[0];
        });
        int maxValue = points.back()[0],n=points.size();
        mapper.resize(maxValue+1);
        for(int i=0;i<n-1;i++)
        {
            auto delta=points[i+1]-points[i];
            Real alpha=delta[1]/delta[0];
            for(int k=static_cast<int>(points[i][0]);k<static_cast<int>(points[i+1][0]);k++)
                mapper[k]=alpha*(k-points[i][0])+points[i][1];
        }
        mapper[maxValue]=maxValue;
    }
} // global