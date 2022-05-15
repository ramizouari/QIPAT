//
// Created by ramizouari on 15/05/22.
//

#include "MedianForm.h"
#include "image/filter/MedianFilter.h"

namespace GUI::spectrum::filter {
            MedianForm::MedianForm(int width, int height, QWidget *parent):FilterForm(width,height,parent)
            {
                layout=new QFormLayout;
                sizeSpinBox=new QSpinBox;
                sizeSpinBox->setRange(1,width);
                sizeSpinBox->setValue(3);
                layout->addRow("Size",sizeSpinBox);
                setLayout(layout);
            }

    image::Image MedianForm::apply(const image::Image &src) const {
        return image::filter::MedianFilter(sizeSpinBox->value()).image::filter::Filter::apply(image::ZeroPadding(src));
    }
} // filter