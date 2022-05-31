//
// Created by ramizouari on 15/05/22.
//

#include "GaussianBlurForm.h"
#include "image/filter/GaussianBlurFilter.h"

namespace GUI::spectrum::filter {
            GaussianBlurForm::GaussianBlurForm(int width, int height, QWidget *parent) : FilterForm(width, height,
                                                                                                    parent) {
                mainLayout = new QFormLayout;

                inputSigmaX = new QDoubleSpinBox;
                inputSigmaY = new QDoubleSpinBox;
                inputCount = new QSpinBox;
                inputSigmaX->setRange(0, width);
                inputSigmaY->setRange(0, height);
                inputSigmaX->setValue(1);
                inputSigmaY->setValue(1);
                inputSigmaX->setSingleStep(0.1);
                inputSigmaY->setSingleStep(0.1);
                inputCount->setRange(1, 100);
                inputCount->setValue(1);
                inputCount->setSingleStep(1);
                mainLayout->addRow("Sigma X", inputSigmaX);
                mainLayout->addRow("Sigma Y", inputSigmaY);
                mainLayout->addRow("Count", inputCount);
                setLayout(mainLayout);
            }

    image::Image GaussianBlurForm::apply(const image::Image &src) const {
        image::filter::GaussianBlurFilter filter(inputSigmaX->value(), inputSigmaY->value(), inputCount->value());
        return filter.image::filter::Filter::apply(image::ZeroPadding(src));
    }
} // filter