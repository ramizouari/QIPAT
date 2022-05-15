//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_TRANSFORMATION_H
#define IMAGEPROCESSING_TRANSFORMATION_H

#include "Image.h"

namespace image {

    template<typename T>
    class Transformation {
    public:
        virtual T apply(const T&operand) const = 0;
        virtual ~Transformation() = default;
    };

    template<typename T>
    class SelfTransformation
    {
    public:
        virtual void apply(T &operand) const = 0;
        virtual ~SelfTransformation() = default;
    };

    template<typename T>
    class NonDeterministicSelfTransformation
    {
    public:
        virtual void apply(T &operand) = 0;
        virtual ~NonDeterministicSelfTransformation() = default;
    };
} // image

#endif //IMAGEPROCESSING_TRANSFORMATION_H
