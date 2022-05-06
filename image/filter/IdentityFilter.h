//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_IDENTITYFILTER_H
#define IMAGEPROCESSING_IDENTITYFILTER_H

#include "ConvolutionalFilter.h"

namespace image::filter {

    class IdentityFilter : public AbstractConvolutionalFilter {
    public:
        [[nodiscard]] Image apply(const Image &src) const override;
        [[nodiscard]] Image apply(Padding &src) const override;
        [[nodiscard]] const Matrix& getKernel() const override;
        [[nodiscard]] Real getComponent(int x, int y) const override;

    };
    } // filter

#endif //IMAGEPROCESSING_IDENTITYFILTER_H
