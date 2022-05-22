//
// Created by ramizouari on 06/05/22.
//

#include "operators.h"

namespace image::filter::morphology::operators
{
    Image erosion(const Image &image, const Image &mask)
    {
        Image dst(image.width,image.height,image.nb_channel,image.max);
        for(auto c=0;c<image.nb_channel;c++) for(auto i=0;i<image.width;i++) for(auto j=0;j<image.height;j++)
                    dst(c,i,j)=dst.max;
        for(int c=0;c<image.nb_channel;c++) for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++)
            for(int p=0;p<mask.width && i+p < image.width;p++) for(int q=0;q<mask.height && j+q < image.height;q++)
                if(mask(c,p,q)>0)
                    dst(c,i,j)=std::min(image(c,i+p,j+q),dst(c,i,j));
        return dst;
    }

    Image dilation(const Image &image, const Image &mask)
    {
        Image dst(image.width,image.height,image.nb_channel,image.max);
        for(int c=0;c<image.nb_channel;c++) for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++)
                    for(int p=0;p<mask.width && i+p < image.width;p++) for(int q=0;q<mask.height && j+q < image.height;q++)
                if(mask(c,p,q)>0)
                    dst(c,i,j)=std::max(image(c,i+p,j+q),dst(c,i,j));
        return dst;
    }

    Image erosion(const Image &image, const Matrix &mask) {
        Image dst(image.width,image.height,image.nb_channel,image.max);
        for(auto c=0;c<image.nb_channel;c++) for(auto i=0;i<image.width;i++) for(auto j=0;j<image.height;j++)
            dst(c,i,j)=dst.max;
        for(int c=0;c<image.nb_channel;c++) for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++)
                    for(int p=0;p<mask.row_dim() && i+p < image.width;p++) for(int q=0;q<mask.col_dim() && j+q < image.height;q++)
                            if(mask[p][q]>0)
                                dst(c,i,j)=std::min(image(c,i+p,j+q),dst(c,i,j));
        return dst;
    }


    Image dilation(const Image &image, const Matrix &mask) {
        Image dst(image.width,image.height,image.nb_channel,image.max);
        for(int c=0;c<image.nb_channel;c++) for(int i=0;i<image.width;i++) for(int j=0;j<image.height;j++)
                    for(int p=0;p<mask.row_dim() && i+p < image.width;p++) for(int q=0;q<mask.col_dim() && j+q < image.height;q++)
                            if(mask[p][q]>0)
                                dst(c,i,j)=std::max(image(c,i+p,j+q),dst(c,i,j));
        return dst;
    }

    Image opening(const Image &image, const Image &mask) {
        return dilation(erosion(image,mask),mask);
    }

    Image closing(const Image &image, const Image &mask) {
        return erosion(dilation(image,mask),mask);
    }

    Image opening(const Image &image, const Matrix &mask) {
        return dilation(erosion(image,mask),mask);
    }

    Image closing(const Image &image, const Matrix &mask) {
        return erosion(dilation(image,mask),mask);
    }

} // operators