//
// Created by ramizouari on 04/06/22.
//
//#define TEST_MODE
#include <QtGui/QImage>
#include "ImageViewTest.h"
#include "gui/imageview.h"

using namespace test;
using GUI::ImageView;
std::unique_ptr<GUI::ImageView> ImageViewTest::view{};

void ImageViewTest::init()
{
    view = std::make_unique<ImageView>();
    auto imgPtr=new image::Image(50,50,1,1);
    QImage img(50,50,QImage::Format_RGB32);
    for(int  i=0;i<50;i++)
        for(int j=0;j<50;j++) {
            (*imgPtr)(i, j) = (i / 10 + j / 10) % 2;
            auto color = (*imgPtr)(i, j) ? Qt::black : Qt::white;
            img.setPixel(i, j, color);
        }
    view->qImage=img;
    view->imageLabel->setPixmap(QPixmap::fromImage(img));
    view->imageData.reset(imgPtr);
}


/*
 * Not a strong test, but it's a start as the functionality of image resizing is not yet implemented.
 * */

void ImageViewTest::testZoomIn()
{
    auto oldFactor=view->factor;
    view->zoomIn();
    QVERIFY(view->factor>oldFactor);
}

/*
 * Not a strong test, but it's a start as the functionality of image resizing is not yet implemented.
 * */
void ImageViewTest::testZoomOut() {
    auto oldFactor=view->factor;
    view->zoomOut();
    QVERIFY(view->factor<oldFactor);
}

void ImageViewTest::testImageSetter() {

}
