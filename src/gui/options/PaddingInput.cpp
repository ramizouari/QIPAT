//
// Created by ramizouari on 03/05/22.
//

#include "PaddingInput.h"

namespace GUI::options {
        PaddingInput::PaddingInput(QWidget *parent) : QComboBox(parent)
        {
            addItem(tr("No padding"));
            addItem(tr("Zero padding"));
            addItem(tr("Constant padding"));
            addItem(tr("Replicate padding"));
            addItem(tr("Mirror padding"));
        }

        std::unique_ptr<image::Padding> PaddingInput::getPadding(int id, image::Image &img) {
            switch(id)
            {
                case 0:
                    return nullptr;
                case 1:
                    return std::make_unique<image::ZeroPadding>(img);
                case 2:
                    return std::make_unique<image::ConstantPadding>(img,255);
                case 3:
                    return std::make_unique<image::TranslationalPadding>(img);
                case 4:
                    return std::make_unique<image::SymmetricPadding>(img);
            }
        }
    } // options