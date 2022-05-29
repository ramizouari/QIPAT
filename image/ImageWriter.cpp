//
// Created by ramizouari on 28/05/22.
//

#include "ImageWriter.h"

namespace image {

    ImageWriter::ImageWriter() {
    }

    ImageWriter::~ImageWriter() = default;

    PNMWriter::PNMWriter() {
    }

    PNMWriter::~PNMWriter() = default;


    void PNMWriter::write(const Image& image, const std::string &filepath, unsigned int imageFormat) {

        switch(imageFormat) {
            case ImageFormat::PBM:
                writePBM(image, filepath);
                break;
            case ImageFormat::PGM:
                writeMultiple(image, filepath, "P5");
                break;
            case ImageFormat::PPM:
                writeMultiple(image, filepath, "P6");
                break;
        }
    }

    std::ofstream PNMWriter::setHeaders(const std::string& filepath, std::string magicNumber, int width, int height, int max) {
        std::ofstream file(filepath, std::ios::binary);

        file<<magicNumber<<std::endl;

        file << height <<" "<< width<<std::endl;
        if (max>0) {
            file << max << std::endl;
        }

        return file;
    }

    void PNMWriter::writePBM(const Image& image, const std::string &filepath) {
        std::ofstream file = setHeaders(filepath, "P4", image.width, image.height, image.max);

        constexpr int byte_size = 8;
        std::bitset<byte_size> bits;

        for (int i = 0; i < image.width*image.height; i+=byte_size) {
            for(int j=0;j<byte_size;j++) {
                bits[j]=image.data[0][(i+j)/image.height][(i+j)%image.height];
                bits[j].flip();
            }
            file.write(reinterpret_cast<char *>(&bits), 1);
        }
        file.close();

    }

    void PNMWriter::writeMultiple(const Image &image, const std::string &filepath, std::string magicNumber){
        std::ofstream file = setHeaders(filepath, magicNumber, image.width, image.height, image.max);

        for(int i=0;i<image.width;i++)
            for(int j=0;j<image.height;j++)
            {
                for (int k=0 ; k<image.nb_channel; k++) {
                    unsigned char pixel = (unsigned char) image.data[k][i][j];
                    file.write(reinterpret_cast<char *>(&pixel), 1);
                }
            }
        file.close();
    }

} // image