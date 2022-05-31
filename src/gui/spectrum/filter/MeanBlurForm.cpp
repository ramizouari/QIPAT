//
// Created by ramizouari on 15/05/22.
//

#include "MeanBlurForm.h"
#include "image/filter/MeanBlurFilter.h"

namespace GUI::spectrum::filter {
    MeanBlurForm::MeanBlurForm(int width, int height, QWidget *parent) : FilterForm(width, height, parent) {
        mainLayout = new QFormLayout;
        inputDimension = new QSpinBox;
        inputDimension->setRange(1, width);
        inputDimension->setValue(width);
        mainLayout->addRow("Dimension", inputDimension);
        setLayout(mainLayout);

    }

    image::Image MeanBlurForm::apply(const image::Image &src) const {
        image::filter::MeanBlurFilter filter(inputDimension->value());
        return filter.image::filter::Filter::apply(image::ZeroPadding(src));
    }
} // filter