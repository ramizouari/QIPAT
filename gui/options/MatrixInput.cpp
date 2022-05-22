//
// Created by ramizouari on 21/05/22.
//

#include <QFormLayout>
#include "MatrixInput.h"

namespace GUI {
    namespace options {
        MatrixInputChoice::MatrixInputChoice(QWidget *parent) :MatrixInput(parent){
            mainLayout = new QVBoxLayout(this);
            inputChoice= new QComboBox(this);
            inputChoice->addItem("Manual");
            inputChoice->addItem("Generator");

            stackedWidget=new QStackedWidget(this);
            mainLayout->addWidget(inputChoice);
            mainLayout->addWidget(stackedWidget);
            connect(inputChoice,&QComboBox::currentIndexChanged,stackedWidget,&QStackedWidget::setCurrentIndex);
            setLayout(mainLayout);
        }

        image::Matrix MatrixInputChoice::getConvolutionMatrix() {
            return dynamic_cast<MatrixInput*>(stackedWidget->currentWidget())->getConvolutionMatrix();
        }

        void MatrixInputChoice::addMatrixInput(MatrixInput *matrixInput) {
            stackedWidget->addWidget(matrixInput);
        }
    } // GUI
} // options