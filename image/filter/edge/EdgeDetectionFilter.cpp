//
// Created by ramizouari on 02/05/22.
//

#include "EdgeDetectionFilter.h"

namespace image::filter::edge
{
            Image EdgeDetectionFilter::apply(const Image &image) const {
                auto I=grayFilter->apply(differentialFilter->apply(image));
                for(int c=0;c<I.nb_channel;c++) for(int i=0;i<I.width;i++) for(int j=0;j<I.height;j++)
                    I(c,i,j)=I(c,i,j)>threshold?I(c,i,j):0;
                return I;
            }

    EdgeDetectionFilter::EdgeDetectionFilter(differential::DifferentialFilter *differentialFilter,
                                             gray::GrayFilter *grayFilter, int threshold):differentialFilter(differentialFilter),
                                                                                          grayFilter(grayFilter),
                                                                                          threshold(threshold)
  {
  }

    Image EdgeDetectionFilter::apply(const Padding &padding) const
    {
        auto I = grayFilter->apply(differentialFilter->apply(padding));
        for (int c = 0; c < I.nb_channel; c++) for (int i = 0; i < I.width; i++) for (int j = 0; j < I.height; j++)
            I(c,i, j) = I(c,i, j) > threshold ? I(c,i, j) : 0;
        return I;
    }
} // edge