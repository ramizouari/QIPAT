//
// Created by ramizouari on 01/05/22.
//

#include "Padding.h"

image::Padding::Padding(Image &img):image(img) {
}

image::Real image::Padding::operator()(int x, int y) const {
    return this->operator()(0,x,y);
}

image::Real image::ConstantPadding::operator()(int c, int x, int y) const {
    if (x<image.width && x >= 0 && y < image.height && y >= 0)
        return image(c,x,y);
    return value;
}

image::ConstantPadding::ConstantPadding(image::Image &img, image::Real value):Padding(img),value(value) {
}


image::ZeroPadding::ZeroPadding(image::Image &image) : ConstantPadding(image,0) {

}


image::Real image::SymmetricPadding::operator()(int c, int x, int y) const {

    x=(x%(2*image.width)+2*image.width)%(2*image.width);
    y=(y%(2*image.height)+2*image.height)%(2*image.height);
    if (x>=image.width)
        x=2*image.width-x-1;
    if(y>=image.height)
        y=2*image.height-y-1;
    return image(c,x,y);
}

image::Real image::TranslationalPadding::operator()(int c, int x, int y) const {
    return image(c,(x%image.width+image.width)%image.width,(y%image.height+image.height)%image.height);
}
