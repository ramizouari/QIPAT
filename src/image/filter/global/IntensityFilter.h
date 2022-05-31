//
// Created by ramizouari on 04/05/22.
//

#ifndef IMAGEPROCESSING_INTENSITYFILTER_H
#define IMAGEPROCESSING_INTENSITYFILTER_H

#include "GlobalFilter.h"
#include "image/utils.h"

namespace image::filter::global {

            class IntensityFilter  : public GlobalFilter {
            protected:
                [[nodiscard]] virtual Real map(Real p) const=0;
            public:
                [[nodiscard]] image::Image apply(const image::Image &image) const override;
            };


            template<image::RealArrayGenerator Generator>
            class GeneratedIntensityFilter : public IntensityFilter {
                const Generator &generator;
            protected:
                [[nodiscard]] Real map(Real p) const override {
                    return generator(p);
                }
            public:
                explicit GeneratedIntensityFilter(const Generator &generator) : generator(generator) {}
            };

        } // global

#endif //IMAGEPROCESSING_INTENSITYFILTER_H
