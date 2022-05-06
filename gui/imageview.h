//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_IMAGEVIEW_H
#define IMAGEPROCESSING_IMAGEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include "image/Image.h"

namespace GUI {
    //QT_BEGIN_NAMESPACE
    //namespace Ui { class ImageView; }
    //QT_END_NAMESPACE

    class ImageView : public QScrollArea {
    Q_OBJECT


    public:
        explicit ImageView(QWidget *parent = nullptr);

        ~ImageView() override;
        void setImage(image::Image *image);
        image::Image* getData();
        void updateQImage();
        void openImage(image::Image *pImage);
    public slots:
        void zoomIn();
        void zoomOut();

    private:
        //Ui::ImageView *ui;
        std::unique_ptr<image::Image> imageData;
        QImage qImage;
        image::Real factor=1;
        QLabel *imageLabel;
    };
} // GUI

#endif //IMAGEPROCESSING_IMAGEVIEW_H
