//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_MEDIANFORM_H
#define IMAGEPROCESSING_MEDIANFORM_H

#include <QSpinBox>
#include "FilterForm.h"

namespace GUI::spectrum::filter {

            class MedianForm  :public FilterForm{
                Q_OBJECT
            public:
                MedianForm(int width, int height, QWidget *parent = nullptr);
                ~MedianForm() override = default;
                image::Image apply(const image::Image &src) const override;
            private:
                QFormLayout *layout;
                QSpinBox* sizeSpinBox;
            };

        } // filter

#endif //IMAGEPROCESSING_MEDIANFORM_H
