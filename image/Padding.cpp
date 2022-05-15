//
// Created by ramizouari on 01/05/22.
//

#include "Padding.h"

image::Padding::Padding(const Image &img):imagePtr(&img) {
}

image::Real image::Padding::operator()(int x, int y) const {
    return this->operator()(0,x,y);
}

const image::Image &image::Padding::image() const {
    return *imagePtr;
}

void image::Padding::setImage(const image::Image &image) {
    imagePtr = &image;
}

image::Real image::ConstantPadding::operator()(int c, int x, int y) const {
    if (x<imagePtr->width && x >= 0 && y < imagePtr->height && y >= 0)
        return (*imagePtr)(c,x,y);
    return value;
}

image::ConstantPadding::ConstantPadding(const image::Image &img, image::Real value):Padding(img),value(value) {
}


image::ZeroPadding::ZeroPadding(const image::Image &image) : ConstantPadding(image,0) {

}


image::Real image::SymmetricPadding::operator()(int c, int x, int y) const {

    x=(x%(2*imagePtr->width)+2*imagePtr->width)%(2*imagePtr->width);
    y=(y%(2*imagePtr->height)+2*imagePtr->height)%(2*imagePtr->height);
    if (x>=imagePtr->width)
        x=2*imagePtr->width-x-1;
    if(y>=imagePtr->height)
        y=2*imagePtr->height-y-1;
    return (*imagePtr)(c,x,y);
}

image::Real image::TranslationalPadding::operator()(int c, int x, int y) const {
    return (*imagePtr)(c,(x%imagePtr->width+imagePtr->width)%imagePtr->width,(y%imagePtr->height+imagePtr->height)%imagePtr->height);
}
