//
// Created by ramizouari on 14/05/22.
//

#ifndef IMAGEPROCESSING_RECTANGLEMASKFORM_H
#define IMAGEPROCESSING_RECTANGLEMASKFORM_H

#include <QWidget>
#include <QFormLayout>
#include <QSpinBox>
#include "MaskForm.h"

namespace GUI::options {

        class RectangleMaskForm:public MaskForm
        {
            Q_OBJECT
        public:

            explicit RectangleMaskForm(int width,int height,QWidget *parent = nullptr);
            ~RectangleMaskForm() override = default;
            std::vector<std::vector<bool>> generateMask() override;
        public:
            QFormLayout* layout;
            QSpinBox *inputX,*inputY,*inputWidth,*inputHeight;
        };

    } // options

#endif //IMAGEPROCESSING_RECTANGLEMASKFORM_H
