//
// Created by ramizouari on 03/05/22.
//

#include <QLabel>
#include "FilterDialog.h"

namespace GUI::options {
    FilterDialog::FilterDialog(QWidget *parent) : QDialog(parent) {
        mainLayout = new QVBoxLayout(this);
        dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        statusBar = new QStatusBar(this);
        layout = new QFormLayout;
        mainLayout->addLayout(layout);
        connect(dialogButtonBox, &QDialogButtonBox::accepted, this, &FilterDialog::accept);
        connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &FilterDialog::reject);
    }
        void FilterDialog::finalize()
        {
            mainLayout->addWidget(dialogButtonBox);
            mainLayout->addWidget(statusBar);
            setLayout(mainLayout);
        }

    PaddingInput *FilterDialog::createPaddingInput() {
        auto paddingInput = new options::PaddingInput(this);
        auto paddingLabel = new QLabel("Padding:",this);
        layout->addRow(paddingLabel, paddingInput);
        return paddingInput;
    }

    GrayFilterInput *FilterDialog::createGrayFilterInput() {
        auto grayFilterInput = new options::GrayFilterInput(this);
        auto grayFilterLabel = new QLabel("Gray Filter:",this);
        layout->addRow(grayFilterLabel, grayFilterInput);
        return grayFilterInput;
    }

    QWidget *FilterDialog::addWidget(const QString& title,QWidget *widget ) {
        auto label = new QLabel(title,this);
        layout->addRow(label,widget);
        return widget;
    }

    QWidget *FilterDialog::addWidget(QWidget *widget) {
        layout->addWidget(widget);
        return widget;
    }

    MatrixInput *FilterDialog::createMatrixInput() {
        auto matrixInput = new options::MatrixInput(this);
        auto matrixLabel = new QLabel("Convolution Matrix:",this);
        layout->addRow(matrixLabel,matrixInput);
        connect(matrixInput, &MatrixInput::validityUpdated, this, [this](MatrixInput::ValidityType type)
        {
            switch(type)
            {
                case MatrixInput::ValidityType::VALID:
                    dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
                    statusBar->showMessage("Valid matrix");
                    break;
                case MatrixInput::ValidityType::INVALID:
                    dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
                    statusBar->showMessage("Invalid matrix");
                    break;
                case MatrixInput::ValidityType::MISSING:
                    dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
                    statusBar->showMessage("Missing values");
                    break;
            }
        });
        return matrixInput;
    }
} // options