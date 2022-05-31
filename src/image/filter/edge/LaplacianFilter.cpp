//
// Created by ramizouari on 02/05/22.
//

#include "LaplacianFilter.h"

namespace image::filter {

    edge::LaplacianFilter::LaplacianFilter(gray::GrayFilter &grayFilter, int threshold,bool includeDiagonal):
    EdgeDetectionFilter(includeDiagonal?static_cast<differential::DifferentialFilter*>(&laplacianOperator):
                        static_cast<differential::DifferentialFilter*>(&laplacianOperatorWithDiagonal),&grayFilter,threshold) {}
} // filter