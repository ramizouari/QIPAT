//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_IMAGEINFORMATIONBAR_H
#define IMAGEPROCESSING_IMAGEINFORMATIONBAR_H

#include <QLabel>
#include "image/Image.h"

namespace GUI {

    class ImageInformationBar: public QLabel {
        Q_OBJECT
    public:
        explicit ImageInformationBar(QWidget *parent = nullptr);
        ~ImageInformationBar() override = default;
        void update(const image::Image& image);

    };

} // GUI

#endif //IMAGEPROCESSING_IMAGEINFORMATIONBAR_H
