//
// Created by ramizouari on 04/06/22.
//

#ifndef IMAGEPROCESSING_IMAGEVIEWTEST_H
#define IMAGEPROCESSING_IMAGEVIEWTEST_H

namespace GUI
{
    class ImageView;
}

#include <QtTest/QtTest>
class ImageViewTest : public QObject
{
    Q_OBJECT
public:
private slots:
    void init();
    void testZoomIn();
    void testZoomOut();
    void testImageSetter();
private:
    static std::unique_ptr<GUI::ImageView> view;
};


#endif //IMAGEPROCESSING_IMAGEVIEWTEST_H
