//
// Created by ramizouari on 04/05/22.
//

#ifndef IMAGEPROCESSING_GLOBALFILTER_H
#define IMAGEPROCESSING_GLOBALFILTER_H

#include "image/filter/Filter.h"

namespace image::filter::global {

    class GlobalFilter :public Filter {
    public:
        [[nodiscard]] Image apply(Padding &src) const override;
        [[nodiscard]] Image apply(const Image &src) const override = 0;
    };

} // Filter

#endif //IMAGEPROCESSING_GLOBALFILTER_H
