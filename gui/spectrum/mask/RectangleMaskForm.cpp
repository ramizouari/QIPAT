//
// Created by ramizouari on 14/05/22.
//

#include "RectangleMaskForm.h"

namespace GUI::options {
        RectangleMaskForm::RectangleMaskForm(int w,int h,QWidget *parent) : MaskForm(w,h,parent){
            layout = new QFormLayout(this);
            inputX = new QSpinBox(this);
            inputY = new QSpinBox(this);
            inputWidth = new QSpinBox(this);
            inputHeight = new QSpinBox(this);
            layout->addRow("X",inputX);
            layout->addRow("Y",inputY);
            layout->addRow("Width",inputWidth);
            layout->addRow("Height",inputHeight);
            inputX->setRange(0,w-1);
            inputY->setRange(0,h-1);
            inputWidth->setRange(1,w-1);
            inputHeight->setRange(1,h-1);
        }

    std::vector<std::vector<bool>> RectangleMaskForm::generateMask() {
        std::vector<std::vector<bool>> mask(width,std::vector<bool>(height,false));
        int a=inputX->value(),b=inputY->value(),c=inputWidth->value(),d=inputHeight->value();
        for(int i=a;i<c;i++) for(int j=b;j<d;j++)
            mask[i][j]=true;
        return mask;
     }
} // options