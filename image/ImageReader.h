//
// Created by ramizouari on 30/04/22.
//

#ifndef IMAGEPROCESSING_IMAGEREADER_H
#define IMAGEPROCESSING_IMAGEREADER_H

#include <string>
#include "Image.h"

namespace image
{
    class Image;
    class ImageReader
    {
    public:
        ImageReader();
        virtual ~ImageReader()=0;
        virtual Image read(const std::string &filename)=0;
    };

    class PNMReader : public ImageReader
    {
        Image readPBM(const std::string &filename,bool binary);
        Image readPGM(const std::string &filename,bool binary);
        Image readPPM(const std::string &filename,bool binary);
    public:
        PNMReader();
        ~PNMReader() override;
        Image read(const std::string &filename) override;
    };


}

#endif //IMAGEPROCESSING_IMAGEREADER_H
