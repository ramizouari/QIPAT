//
// Created by ramizouari on 30/04/22.
//
#include "reader.h"
#include "Image.h"
#include "functional/functional.h"
#include <regex>
#include <fstream>
#include <ranges>
#include <iostream>


image::ImageReader::ImageReader() {

}

image::ImageReader::~ImageReader() {

}

image::PGMReader::PGMReader() {

}

image::PGMReader::~PGMReader() = default;


image::Image image::PGMReader::read(const std::string &filename) {
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


image::Image image::PGMReader::readPGM(const std::string &filename,bool binary)
{
    std::ifstream file(filename,binary?std::ios::binary:std::ios::in);
    std::string magicNumber;
    file >> magicNumber;
    std::string tmp;
    int counter = 0;
    file.ignore();
    auto optComment = [&]() {
        while(std::getline(file,tmp))
        {
            if(tmp[0]=='#')
                continue;
            else
                break;
        }
    };
    optComment();
    int width,height,maxValue;
    {
        std::stringstream str(tmp);
        str >> height >> width;
        optComment();
    }
    {
        std::stringstream str(tmp);
        str >> maxValue;
    }
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

image::Image image::PGMReader::readPPM(const std::string &filename,bool binary)
{
    constexpr int nb_channels=3;
    std::ifstream file(filename,binary?std::ios::binary:std::ios::in);
    std::string magicNumber;
    file >> magicNumber;
    file.ignore();
    std::string tmp;
    int counter = 0;
    auto optComment = [&]() {
        while(std::getline(file,tmp))
        {
            if(tmp[0]=='#')
                continue;
            else
                break;
        }
    };
    optComment();
    int width,height,maxValue;
    {
        std::stringstream str(tmp);
        str >> height >> width;
        optComment();
    }
    {
        std::stringstream str(tmp);
        str >> maxValue;
    }
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

image::Image image::PGMReader::readPBM(const std::string &filename,bool binary) {
    std::ifstream file(filename,binary?std::ios::binary:std::ios::in);
    std::string magicNumber;
    file >> magicNumber;
    file.ignore();
    std::string tmp;
    auto optComment = [&]() {
        while(std::getline(file,tmp))
        {
            if(tmp[0]=='#')
                continue;
            else
                break;
        }
    };
    optComment();
    std::stringstream str(tmp);
    int width,height;
    str >> height >> width;
    tensor<2> data=make_tensor(width,height);
    constexpr int bit_size=8;
    if (binary)
    {
        int size=(width*height)/bit_size;
        auto readData=std::make_unique<unsigned char[]>(size);
        file.read(reinterpret_cast<char *>(readData.get()), size);
        std::bitset<bit_size> bits;
        for (int i = 0; i < width*height; i+=bit_size)
        {
            bits = std::bitset<bit_size>(readData[i/bit_size]);
            for(int j=0;j<bit_size;j++)
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
