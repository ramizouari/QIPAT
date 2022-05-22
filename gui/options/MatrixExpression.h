//
// Created by ramizouari on 21/05/22.
//

#ifndef IMAGEPROCESSING_MATRIXEXPRESSION_H
#define IMAGEPROCESSING_MATRIXEXPRESSION_H

#include <QCheckBox>
#include "MatrixInput.h"

namespace GUI::options {

        class MatrixExpression : public MatrixInput {
                Q_OBJECT
        public:
            explicit MatrixExpression(QWidget *parent = nullptr);
            ~MatrixExpression() override = default;
            image::Matrix getConvolutionMatrix() override;
        private:
            QFormLayout *mainLayout;
            QPlainTextEdit *generatorExpression;
            QSpinBox *rowSpinBox;
            QSpinBox *columnSpinBox;
            QCheckBox *normalizeCheckBox;
        };

    } // options

#endif //IMAGEPROCESSING_MATRIXEXPRESSION_H
