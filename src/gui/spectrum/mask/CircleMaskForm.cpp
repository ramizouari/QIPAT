//
// Created by ramizouari on 15/05/22.
//

#include "CircleMaskForm.h"

namespace GUI {
    namespace options {
        CircleMaskForm::CircleMaskForm(int width, int height, QWidget *parent) : MaskForm(width, height, parent) {
            layout = new QFormLayout(this);
            inputX = new QSpinBox(this);
            inputY = new QSpinBox(this);
            inputRadius = new QSpinBox(this);
            layout->addRow("X", inputX);
            layout->addRow("Y", inputY);
            layout->addRow("Radius", inputRadius);
            inputX->setRange(0, width - 1);
            inputY->setRange(0, height - 1);
            inputRadius->setRange(1, width - 1);

        }

        std::vector<std::vector<bool>> CircleMaskForm::generateMask() {
            std::vector<std::vector<bool>> mask(width, std::vector<bool>(height, false));
            int a = inputX->value(), b = inputY->value(), r = inputRadius->value();
            for(int i=0;i<width;i++) for(int j=0;j<height;j++)
                mask[i][j] = (i-a)*(i-a)+(j-b)*(j-b)<=r*r;
            return mask;
        }
    } // GUI
} // options