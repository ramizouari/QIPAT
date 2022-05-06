//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_FILTER_H
#define IMAGEPROCESSING_FILTER_H

#include "image/Image.h"
#include "image/Padding.h"

namespace image::filter {


    class Filter {
    public:
        virtual ~Filter() = default;

        void apply(const Image &src, Image &dst) const;
        [[nodiscard]] virtual Image apply(const Image &src) const = 0;
        [[nodiscard]] virtual Image apply(const Padding &src) const = 0;
        Image operator()(const Image &src) const;
        void operator()(const Image &src, Image &dst) const;
    };



} // image

#endif //IMAGEPROCESSING_FILTER_H
