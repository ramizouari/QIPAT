//
// Created by ramizouari on 30/04/22.
//
#include "ImageReader.h"
#include "Image.h"
#include "functional/functional.h"
#include <regex>
#include <fstream>
#include <ranges>
#include <iostream>
#include <bitset>


image::ImageReader::ImageReader() {

}

image::ImageReader::~ImageReader() {

}

image::PNMReader::PNMReader() {

}

image::PNMReader::~PNMReader() = default;


image::Image image::PNMReader::read(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open fileMenu");
    }
    std::string magicNumber;
    std::smatch match;
    file >> magicNumber;
    std::regex regex("P[1-6]");
    if(!std::regex_match(magicNumber,match,regex))
        throw std::runtime_error("Wrong magic number");
    file.close();
    bool binary=magicNumber[1] > '3';
    switch(magicNumber[1])
    {
        case '1':
        case '4':
            return readPBM(filename,binary);
        case '2':
        case '5':
            return readPGM(filename,binary);
        case '3':
        case '6':
            return readPPM(filename,binary);
    }

}


image::Image image::PNMReader::readPGM(const std::string &filename, bool binary)
{
    std::ifstream file(filename,binary?std::ios::binary:std::ios::in);
    std::string magicNumber;
    file >> magicNumber;
    std::string tmp;
    int counter = 0;
    file.ignore();
    auto optComment = [&]() {
        while(file.peek() == '#')
            std::getline(file,tmp);
    };
    optComment();
    int width,height,maxValue;
    file >> height >> width;
    file.ignore();
    optComment();
    file >> maxValue;
    file.ignore();
    std::cout << maxValue << std::endl;
    tensor<2> data=make_tensor(width,height);
    for(int i=0;i<width;i++,std::cout << std::endl) for(int j=0;j<height;j++)
    {
        if(binary) {
            unsigned char datum;
            file.read(reinterpret_cast<char*>(&datum),1);
            data[i][j] = datum;
        }
        else file >> data[i][j];
    }
    return image::Image(std::move(data),maxValue);
}

image::Image image::PNMReader::readPPM(const std::string &filename, bool binary)
{
    constexpr int nb_channels=3;
    std::ifstream file(filename,binary?std::ios::binary:std::ios::in);
    std::string magicNumber;
    file >> magicNumber;
    file.ignore();
    std::string tmp;
    int counter = 0;
    auto optComment = [&]() {
        while(file.peek() == '#')
            std::getline(file,tmp);
    };
    optComment();
    int width,height,maxValue;
    file >> height >> width;
    file.ignore();
    optComment();
    file >> maxValue;
    file.ignore();
    tensor<3> data=image::make_tensor(nb_channels,width,height);
     for(int j=0;j<width;j++) for(int k=0;k<height;k++) for(int i=0;i<nb_channels;i++)
    {
         if(binary)
         {
             unsigned char datum;
             file.read(reinterpret_cast<char*>(&datum),1);
             data[i][j][k] = datum;
         }
         else file >> data[i][j][k];
     }
    return image::Image(std::move(data),maxValue);
}

image::Image image::PNMReader::readPBM(const std::string &filename, bool binary) {
    std::ifstream file(filename,binary?std::ios::binary:std::ios::in);
    std::string magicNumber;
    file >> magicNumber;
    file.ignore();
    std::string tmp;
    auto optComment = [&]() {
        while(file.peek() == '#')
            std::getline(file,tmp);
    };
    optComment();
    int width,height;
    file >> height >> width;
    file.ignore();
    tensor<2> data=make_tensor(width,height);
    constexpr int byte_size=8;
    if (binary)
    {
        int size= (width*height) / byte_size;
        auto readData=std::make_unique<unsigned char[]>(size);
        file.read(reinterpret_cast<char *>(readData.get()), size);
        std::bitset<byte_size> bits;
        for (int i = 0; i < width*height; i+=byte_size)
        {
            bits = std::bitset<byte_size>(readData[i / byte_size]).flip();
            for(int j=0; j < byte_size && (i+j)/height < width; j++)
                data[(i+j)/height][(i+j)%height]=bits[j];
        }

    }
    else for(auto &R:data) for (auto &c: R)
    {
        file >> c;
        c = 1 - c;
    }
    return image::Image(std::move(data),1);
}
