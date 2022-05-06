//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_ROBERTSOPERATOR_H
#define IMAGEPROCESSING_ROBERTSOPERATOR_H

#include "image/filter/ConvolutionalFilter.h"
#include "DifferentialFilter.h"

namespace image::filter::differential {

    class RobertsOperator : public DifferentialFilter {
        static ConvolutionalFilter Gx,Gy;
    public:
        ~RobertsOperator() override = default;
        [[nodiscard]] Image apply(const image::Image &src) const override;
        [[nodiscard]] Image apply(const image::Padding &src) const override;
    };

} // differential

#endif //IMAGEPROCESSING_ROBERTSOPERATOR_H
