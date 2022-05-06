//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMVIEW_H
#define IMAGEPROCESSING_SPECTRUMVIEW_H

#include <QWidget>
#include "image/Image.h"

namespace GUI::spectrum {

        class SpectrumView :public QWidget {
        public:
            explicit SpectrumView(const image::Image &img,QWidget *parent = nullptr);
        };

    } // spectrum

#endif //IMAGEPROCESSING_SPECTRUMVIEW_H
