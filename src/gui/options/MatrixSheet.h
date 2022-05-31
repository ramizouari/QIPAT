//
// Created by ramizouari on 05/05/22.
//

#ifndef IMAGEPROCESSING_MATRIXSHEET_H
#define IMAGEPROCESSING_MATRIXSHEET_H

#include <QPlainTextEdit>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <set>
#include "image/Image.h"
#include "MatrixInput.h"

namespace GUI::options {

        class MatrixSheet: public MatrixInput {
            Q_OBJECT
        public:
            enum class ValidityType
            {
                VALID,
                MISSING,
                INVALID
            };
            explicit MatrixSheet(QWidget *parent = nullptr);
            ~MatrixSheet() override = default;
            image::Matrix getConvolutionMatrix() override;
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

#endif //IMAGEPROCESSING_MATRIXSHEET_H
