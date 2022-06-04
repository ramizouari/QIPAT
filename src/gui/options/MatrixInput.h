//
// Created by ramizouari on 21/05/22.
//

#ifndef IMAGEPROCESSING_MATRIXINPUT_H
#define IMAGEPROCESSING_MATRIXINPUT_H

#include <QWidget>
#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "image/Image.h"

namespace GUI::options {

        class MatrixInput :public QWidget {
            Q_OBJECT
        public:
            using QWidget::QWidget;
            ~MatrixInput() override = default;
            virtual image::Matrix getConvolutionMatrix() = 0;
        };

        class MatrixInputChoice: public MatrixInput {
        Q_OBJECT
        public:
            explicit MatrixInputChoice(QWidget *parent = nullptr);
            ~MatrixInputChoice() override = default;
            image::Matrix getConvolutionMatrix() override;
            void addMatrixInput(MatrixInput* matrixInput);
        private:
            QComboBox *inputChoice;
            QStackedWidget *stackedWidget;
            QVBoxLayout *mainLayout;
        };

    } // options

#endif //IMAGEPROCESSING_MATRIXINPUT_H
