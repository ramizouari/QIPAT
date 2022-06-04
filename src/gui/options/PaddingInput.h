//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_PADDINGINPUT_H
#define IMAGEPROCESSING_PADDINGINPUT_H

#include <QComboBox>
#include "image/Padding.h"

namespace GUI::options {

        class PaddingInput : public QComboBox
        {
            Q_OBJECT
        public:
            explicit PaddingInput(QWidget *parent = nullptr);
            ~PaddingInput() override = default;
            static std::unique_ptr<image::Padding> getPadding(int id, image::Image& img);
        };

    } // options

#endif //IMAGEPROCESSING_PADDINGINPUT_H
