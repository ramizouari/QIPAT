//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_FILTER_H
#define IMAGEPROCESSING_FILTER_H

#include "image/Image.h"
#include "image/Padding.h"
#include "image/Operator.h"

namespace image::filter {


    class Filter : public Operator<Image>, public Transformation<Padding,Image> {
    public:
        ~Filter() override = default;

        void apply(const Image &src, Image &dst) const;
        [[nodiscard]] Image apply(const Image &src) const override = 0;
        [[nodiscard]] Image apply(Padding &src) const override = 0;
        [[nodiscard]] Image apply(Padding &&src) const;
        Image operator()(const Image &src) const;
        void operator()(const Image &src, Image &dst) const;
    };



} // image

#endif //IMAGEPROCESSING_FILTER_H
