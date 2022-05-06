//
// Created by ramizouari on 04/05/22.
//

#ifndef IMAGEPROCESSING_INTENSITYMAPPER_H
#define IMAGEPROCESSING_INTENSITYMAPPER_H

#include "IntensityFilter.h"

namespace image::filter::global {

    class IntensityMapper :public IntensityFilter
    {
        std::vector<Real> mapper;
    protected:
        [[nodiscard]] Real map(Real c) const override;
    public:
        explicit IntensityMapper(const std::vector<Real> &mapper);
        explicit IntensityMapper(std::vector<Real> &&mapper);
        explicit IntensityMapper(std::vector<std::pair<Real,Real>> points);
        explicit IntensityMapper(std::vector<Vector2> points);

    };

} // global

#endif //IMAGEPROCESSING_INTENSITYMAPPER_H
