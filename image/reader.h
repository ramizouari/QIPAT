//
// Created by ramizouari on 30/04/22.
//

#ifndef IMAGEPROCESSING_READER_H
#define IMAGEPROCESSING_READER_H

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

    class PGMReader : public ImageReader
    {
        Image readPBM(const std::string &filename,bool binary);
        Image readPGM(const std::string &filename,bool binary);
        Image readPPM(const std::string &filename,bool binary);
    public:
        PGMReader();
        ~PGMReader() override;
        Image read(const std::string &filename) override;
    };


}

#endif //IMAGEPROCESSING_READER_H
