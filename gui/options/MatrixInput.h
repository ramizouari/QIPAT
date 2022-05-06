//
// Created by ramizouari on 05/05/22.
//

#ifndef IMAGEPROCESSING_MATRIXINPUT_H
#define IMAGEPROCESSING_MATRIXINPUT_H

#include <QPlainTextEdit>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <set>
#include "image/Image.h"

namespace GUI::options {

        class MatrixInput:public QWidget {
            Q_OBJECT
        public:
            enum class ValidityType
            {
                VALID,
                MISSING,
                INVALID
            };
            explicit MatrixInput(QWidget *parent = nullptr);
            ~MatrixInput() override = default;
            image::Matrix getConvolutionMatrix();
        signals:
            void validityUpdated(ValidityType isValid);
        private:
            QTableWidget* tableWidget;
            QGridLayout *mainLayout;
            QPushButton *addRowButton, *addColumnButton, *removeRowButton, *removeColumnButton;
            std::set<std::pair<int,int>> invalidCells, validCells;
            void emitValiditySignal();
        };

    } // options

#endif //IMAGEPROCESSING_MATRIXINPUT_H
