//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMVIEW_H
#define IMAGEPROCESSING_SPECTRUMVIEW_H

#include <QLabel>
#include "image/Image.h"
#include "gui/imageview.h"

namespace GUI::spectrum {

        class SpectrumView :public ImageView{
        Q_OBJECT
        public:
            explicit SpectrumView(const image::Image &img,QWidget *parent = nullptr);
            ~SpectrumView() override = default;
        };

    } // spectrum

#endif //IMAGEPROCESSING_SPECTRUMVIEW_H
