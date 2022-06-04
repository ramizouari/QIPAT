//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_GRAYFILTERINPUT_H
#define IMAGEPROCESSING_GRAYFILTERINPUT_H

#include <QComboBox>
#include "image/filter/gray/GrayFilter.h"

namespace GUI::options {

        class GrayFilterInput : public QComboBox {
        Q_OBJECT
        public:
            explicit GrayFilterInput(QWidget *parent = nullptr);
            ~GrayFilterInput() override = default;
            static image::filter::gray::GrayFilter& getGrayFilter(int id);

        };

    } // options

#endif //IMAGEPROCESSING_GRAYFILTERINPUT_H
