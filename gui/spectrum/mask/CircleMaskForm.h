//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_CIRCLEMASKFORM_H
#define IMAGEPROCESSING_CIRCLEMASKFORM_H

#include <QSpinBox>
#include <QFormLayout>
#include "MaskForm.h"

namespace GUI::options {

        class CircleMaskForm:public MaskForm
        {
        Q_OBJECT
        public:
            explicit CircleMaskForm(int width,int height,QWidget *parent = nullptr);
            ~CircleMaskForm() override = default;
            std::vector<std::vector<bool>> generateMask() override;
        private:
            QFormLayout* layout;
            QSpinBox *inputX,*inputY,*inputRadius;
        };

    } // options

#endif //IMAGEPROCESSING_CIRCLEMASKFORM_H
