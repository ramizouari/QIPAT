//
// Created by ramizouari on 03/05/22.
//

#include "GrayFilterInput.h"
#include "image/filter/gray/utils.h"

namespace GUI::options {
        image::filter::gray::GrayFilter &GrayFilterInput::getGrayFilter(int id) {
            switch(id)
            {
                case 0:
                    return image::filter::gray::maxChannelFilter;
                case 1:
                    return image::filter::gray::meanChannelFilter;
                case 2:
                    return image::filter::gray::rec601Filter;
                case 3:
                    return image::filter::gray::rec709Filter;
                case 4:
                    return image::filter::gray::l1NormFilter;
                case 5:
                    return image::filter::gray::l2NormFilter;
            }
        }

    GrayFilterInput::GrayFilterInput(QWidget *parent) : QComboBox(parent) {
        addItem(tr("Max Channel"));
        addItem(tr("Mean Channel"));
        addItem(tr("Rec.601"));
        addItem(tr("Rec.709"));
        addItem(tr("L1 Norm"));
        addItem(tr("L2 Norm"));

    }
} // options