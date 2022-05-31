//
// Created by ramizouari on 30/04/22.
//
#include "Image.h"

image::Image::Image(int width, int height, int nb_channel,int max) : data(nb_channel, std::vector<std::vector<Real>>(width, std::vector<Real>(height, 0))),
                                                             width(width), height(height), nb_channel(nb_channel),max(max)
{
}

image::Real& image::Image::operator()(int i, int j, int k){
    return data[i][j][k];
}

const image::Real & image::Image::operator()(int i, int j, int k) const {
    return data[i][j][k];
}

image::Real &image::Image::operator()(int i, int j) {
    return data.front()[i][j];
}

const image::Real &image::Image::operator()(int i, int j) const {
    return data.front()[i][j];
}

image::Image::Image(const Image &other) {
    data = other.data;
    width = other.width;
    height = other.height;
    nb_channel = other.nb_channel;
    max=other.max;
}

image::Image::Image(Image &&other) noexcept {
    data = std::move(other.data);
    width = other.width;
    height = other.height;
    nb_channel = other.nb_channel;
    max=other.max;
}

image::Image &image::Image::operator=(const Image &other) {
    data = other.data;
    width = other.width;
    height = other.height;
    nb_channel = other.nb_channel;
    max=other.max;
    return *this;
}

image::Image &image::Image::operator=(Image &&other) noexcept {
    data = std::move(other.data);
    width = other.width;
    height = other.height;
    nb_channel = other.nb_channel;
    max=other.max;
    return *this;
}

image::Image::Image(tensor<2> &other,int max): data(1, other),max(max) {
    update_parameters();
}

image::Image::Image(tensor<2> &&other,int max) noexcept: data(1),max(max) {
    data.front() = std::move(other);
    update_parameters();
}

image::Image::Image(tensor<3> &&other,int max) noexcept : data(std::move(other)),max(max)
{
    update_parameters();
}

image::Image::Image(tensor<3> &other,int max): data(other),max(max)
{
    update_parameters();
}

void image::Image::update_parameters() {
    width = data.front().size();
    height = data.front().front().size();
    nb_channel = data.size();
}

image::Image &image::Image::operator=(tensor<2> &&other) {
    data.front() = std::move(other);
    update_parameters();
    return *this;
}

image::Image &image::Image::operator=(const tensor<2> &other) {
    data.front() = other;
    update_parameters();
    return *this;
}

image::Image &image::Image::operator=(const tensor<3> &other) {
    data = other;
    update_parameters();
    return *this;
}

image::Image &image::Image::operator=(tensor<3> &&other) {
    data = std::move(other);
    update_parameters();
    return *this;
}


image::Image::~Image() = default;

image::MonoImage::MonoImage(int width, int height, int max) : Image(width, height, max) {

}

image::MonoImage::MonoImage(const MonoImage &other) = default;

image::MonoImage::~MonoImage() = default;

auto &image::MonoImage::operator[](int i) {
    return data.front()[i];
}

const auto& image::MonoImage::operator[](int i) const {
    return data.front()[i];
}

image::MonoImage::MonoImage(MonoImage &&other) noexcept: Image(std::move(other)) {
}

auto &image::PolyImage::operator[](int i) {
    return data[i];
}

const auto &image::PolyImage::operator[](int i) const {
    return data[i];
}


