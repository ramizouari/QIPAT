//
// Created by ramizouari on 01/05/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ImageView.h" resolved

#include "imageview.h"
#include <QApplication>
#include <QScreen>

constexpr std::uint64_t MAX_QIMAGE_SIZE=1<<26;

namespace GUI {
    constexpr image::Real MAX_RGB = 255;
    ImageView::ImageView(QWidget *parent) : QScrollArea(parent)
    {
        imageLabel =new QLabel(this);
        setWidget(imageLabel);

        setContentsMargins(0,0,0,0);
        imageLabel->setAlignment(Qt::AlignCenter);
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        int height = screenGeometry.height();
        int width = screenGeometry.width();
        setAlignment(Qt::AlignCenter);
        setContentsMargins(0,0,0,0);
        setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    }

    ImageView::~ImageView() = default;

    void ImageView::setImage(image::Image *image)
    {
        imageData.reset(image);
        image::Real k=MAX_RGB/image->max;
        if (imageData->nb_channel == 1) {
            qImage = QImage(image->height, image->width, QImage::Format_Grayscale8);
            for (int i = 0; i < image->width; i++)
                for (int j = 0; j < image->height; j++)
                    qImage.setPixel(j, i, qRgb(k*(*imageData)(i, j), k*(*imageData)(i, j), k*(*imageData)(i, j)));
        } else {
            qImage = QImage(image->height, image->width, QImage::Format_RGB888);
            for (int i = 0; i < image->width; i++)
                for (int j = 0; j < image->height; j++)
                    qImage.setPixel(j, i,
                                    qRgb(k*imageData->data[0][i][j], k*imageData->data[1][i][j], k*imageData->data[2][i][j]));
        }
        imageLabel->setPixmap(QPixmap::fromImage(qImage.scaled(qImage.size()*factor,Qt::KeepAspectRatio,Qt::FastTransformation)));
        imageLabel->setMinimumSize(imageLabel->pixmap().size());
        imageLabel->setMaximumSize(imageLabel->pixmap().size());
    }

    image::Image *ImageView::getData() {
        return imageData.get();
    }

    void ImageView::updateQImage() {
        image::Real k=MAX_RGB/imageData->max;
        if(imageData->nb_channel==1) {
             for (int i = 0; i < imageData->width; i++)
                for (int j = 0; j < imageData->height; j++)
                    qImage.setPixel(j, i, qRgb(k*(*imageData)(i,j),k*(*imageData)(i,j),k*(*imageData)(i,j)));
        }
        else
        {
            for (int i = 0; i < imageData->width; i++)
                for (int j = 0; j < imageData->height; j++)
                    qImage.setPixel(j, i, qRgb(k*imageData->data[0][i][j], k*imageData->data[1][i][j], k*imageData->data[2][i][j]));
        }
        imageLabel->setPixmap(QPixmap::fromImage(qImage.scaled(qImage.size()*factor,Qt::KeepAspectRatio,Qt::FastTransformation)));
        imageLabel->setMinimumSize(imageLabel->pixmap().size());
        imageLabel->setMaximumSize(imageLabel->pixmap().size());

    }

    void ImageView::zoomIn() {
        if(qImage.width()*qImage.height()*factor > MAX_QIMAGE_SIZE)
            return;
        factor*=1.2;
        imageLabel->setPixmap(QPixmap::fromImage(qImage.scaled(qImage.size()*factor,Qt::KeepAspectRatio,Qt::FastTransformation)));
        imageLabel->setMinimumSize(imageLabel->pixmap().size());
        imageLabel->setMaximumSize(imageLabel->pixmap().size());
    }

    void ImageView::zoomOut() {
        if(std::min(qImage.width(),qImage.height())/factor < 1)
            return;
        factor/=1.2;
        imageLabel->setPixmap(QPixmap::fromImage(qImage.scaled(qImage.size()*factor,Qt::KeepAspectRatio,Qt::FastTransformation)));
        imageLabel->setMinimumSize(imageLabel->pixmap().size());
        imageLabel->setMaximumSize(imageLabel->pixmap().size());
    }

    void ImageView::openImage(image::Image *pImage) {
        factor=1;
        setImage(pImage);
    }
} // GUI
