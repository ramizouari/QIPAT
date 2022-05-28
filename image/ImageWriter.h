//
// Created by ramizouari on 28/05/22.
//

#ifndef IMAGEPROCESSING_IMAGEWRITER_H
#define IMAGEPROCESSING_IMAGEWRITER_H


#include <string>
#include "Image.h"


namespace image {

    class image;
    class ImageWriter
    {
    public:
        ImageWriter();
        virtual ~ImageWriter()=0;
        virtual void write(Image image, const std::string &filename)=0;
    };

    class PNMWriter : public ImageWriter
    {
        void writePBM(const std::string &filename, bool binary);
        void writePGM(const std::string &filename, bool binary);
        void writePPM(const std::string &filename, bool binary);
    public:
        PNMWriter();
        ~PNMWriter() override;
        void write(Image image, const std::string &filename) override;
    };

} // image

#endif //IMAGEPROCESSING_IMAGEWRITER_H
