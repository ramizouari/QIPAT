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

    void PNMWriter::write(Image image, const std::string &filename) {}

    void PNMWriter::writePBM(const std::string &filename, bool binary) {}

    void PNMWriter::writePGM(const std::string &filename, bool binary) {}

    void PNMWriter::writePPM(const std::string &filename, bool binary) {}

} // image