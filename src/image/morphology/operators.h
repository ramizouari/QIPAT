//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_OPERATORS_H
#define IMAGEPROCESSING_OPERATORS_H

#include "image/Image.h"

namespace image::filter::morphology::operators
{
    Image erosion(const Image &image, const Image &mask);
    Image erosion(const Image &image, const Matrix &mask);

    Image dilation(const Image &image, const Image &mask);
    Image dilation(const Image &image, const Matrix &mask);


    Image opening(const Image &image, const Image &mask);
    Image closing(const Image &image, const Image &mask);
    Image opening(const Image &image, const Matrix &mask);
    Image closing(const Image &image, const Matrix &mask);

} // operators

#endif //IMAGEPROCESSING_OPERATORS_H
