//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_OPERATOR_H
#define IMAGEPROCESSING_OPERATOR_H

#include "Image.h"

namespace image {

    template<typename A,typename B=A>
    class Operator {
    public:
        virtual B apply(const A&operand) const = 0;
        virtual ~Operator() = default;
    };


    template<typename A,typename B=A>
    class NonDeterministicOperator {
    public:
        virtual B apply(const A&operand)  = 0;
        virtual ~NonDeterministicOperator() = default;
    };

    template<typename A,typename B=void>
    class Transformation
    {
    public:
        virtual B apply(A &operand) const = 0;
        virtual ~Transformation() = default;
    };

    template<typename T>
    class NonDeterministicTransformation
    {
    public:
        virtual void apply(T &operand) = 0;
        virtual ~NonDeterministicTransformation() = default;
    };
} // image

#endif //IMAGEPROCESSING_OPERATOR_H
