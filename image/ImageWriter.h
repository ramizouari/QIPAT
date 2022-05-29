//
// Created by ramizouari on 28/05/22.
//

#ifndef IMAGEPROCESSING_IMAGEWRITER_H
#define IMAGEPROCESSING_IMAGEWRITER_H


#include <string>
#include "Image.h"
#include "ImageFormat.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <bitset>

namespace image {

    class ImageWriter
    {
    public:
        ImageWriter();
        virtual ~ImageWriter()=0;
        virtual void write(const Image& image, const std::string &filepath, unsigned int imageFormat)=0;
    };

    class PNMWriter : public ImageWriter
    {
        /**
         * Write PBM image to binary
         * @param image
         * @param filepath
         */
        void writePBM(const Image& image, const std::string &filepath);
        std::ofstream setHeaders(const std::string &filepath, std::string magicNumber, int width, int height, int max = 0);
        void writeMultiple(const Image& image, const std::string& filepath, std::string magicNumber);

    public:
        PNMWriter();
        ~PNMWriter() override;
        void write(const Image& image, const std::string &filepath, unsigned int imageFormat) override;
    };

} // image

#endif //IMAGEPROCESSING_IMAGEWRITER_H
