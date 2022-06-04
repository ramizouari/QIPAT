//
// Created by ramizouari on 02/05/22.
//

#include "SobelFilter.h"
#include "functional/zip.h"

namespace image::filter::edge {
    SobelFilter::SobelFilter(gray::GrayFilter &grayFilter,int threshold):EdgeDetectionFilter(&sobelOperator,&grayFilter,threshold) {}

} // filter