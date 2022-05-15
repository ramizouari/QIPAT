//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_GAUSSIANBLURFORM_H
#define IMAGEPROCESSING_GAUSSIANBLURFORM_H

#include <QDoubleSpinBox>
#include <QGroupBox>
#include "FilterForm.h"

namespace GUI::spectrum::filter {

            class GaussianBlurForm : public FilterForm {
            Q_OBJECT
        public:
            explicit GaussianBlurForm(int width, int height, QWidget *parent = nullptr);
            ~GaussianBlurForm() override = default;

                [[nodiscard]] image::Image apply(const image::Image &src) const override;

            private:
                QFormLayout *mainLayout;
                QDoubleSpinBox *inputSigmaX, *inputSigmaY;
                QSpinBox *inputCount;
            };

        } // filter

#endif //IMAGEPROCESSING_GAUSSIANBLURFORM_H
