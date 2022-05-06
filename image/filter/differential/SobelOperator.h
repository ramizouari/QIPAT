//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_SOBELOPERATOR_H
#define IMAGEPROCESSING_SOBELOPERATOR_H

#include "DifferentialFilter.h"
#include "image/filter/ConvolutionalFilter.h"

namespace image::filter::differential {

            class SobelOperator : public DifferentialFilter
            {
                static ConvolutionalFilter Gx,Gy;
            public:
                ~SobelOperator() override = default;
                [[nodiscard]] Image apply(const image::Image &src) const override;
                [[nodiscard]] Image apply(Padding &src) const override;
            };

        } // differential

#endif //IMAGEPROCESSING_SOBELOPERATOR_H
