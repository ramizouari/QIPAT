//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_LAPLACIANOPERATOR_H
#define IMAGEPROCESSING_LAPLACIANOPERATOR_H

#include "DifferentialFilter.h"
#include "image/filter/ConvolutionalFilter.h"

namespace image::filter::differential {

            class LaplacianOperator :public DifferentialFilter,public AbstractConvolutionalFilter
            {
                static Matrix kernel;
            public:
                [[nodiscard]] const Matrix& getKernel() const override;
                [[nodiscard]] Image apply(const Image &src) const override;
                [[nodiscard]] Image apply(Padding &src) const override;
                [[nodiscard]] Real getComponent(int i, int j) const override;
            };

        class LaplacianOperatorWithDiagonal :public DifferentialFilter,public AbstractConvolutionalFilter
        {
            static Matrix kernel;
        public:
            [[nodiscard]] const Matrix& getKernel() const override;
            [[nodiscard]] Image apply(const Image &src) const override;
            [[nodiscard]] Image apply(Padding &src) const override;
            [[nodiscard]] Real getComponent(int i, int j) const override;
        };

        } // differential

#endif //IMAGEPROCESSING_LAPLACIANOPERATOR_H
