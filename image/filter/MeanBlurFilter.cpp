//
// Created by ramizouari on 02/05/22.
//

#include "MeanBlurFilter.h"

namespace image::filter
{

    Image SmallMeanBlurFilter::apply(Padding &src) const {
        Image dst(src.image().width,src.image().height,src.image().nb_channel,src.image().max);
        int s1=size/2,s2=size/2;
        for(int c=0;c<src.image().nb_channel;c++) for(int i=0;i<src.image().width;i++) for(int j=0;j<src.image().height;j++) for(int p=0;p<size;p++) for(int q=0;q<size;q++)
                            dst.data[c][i][j]+=src(c,i+p-s1,j+q-s2);
        for(int c=0;c<src.image().nb_channel;c++) for(int i=0;i<src.image().width;i++) for(int j=0;j<src.image().height;j++)
                    dst.data[c][i][j]/=size*size;
        return dst;
    }

    Image SmallMeanBlurFilter::apply(const Image &src) const {
        int s1=size/2,s2=size/2;
        Image dst(src.width-2*s1,src.height-2*s2,src.nb_channel,src.max);
        for(int c=0;c<src.nb_channel;c++) for(int i=0;i<src.width-2*s1;i++) for(int j=0;j<src.height-2*s2;j++)
                    for(int p=0;p<size;p++) for(int q=0;q<size;q++)
                            dst.data[c][i][j]+=src(c,i+s1-p,j+s2-p);
        for(auto &C:dst.data) for(auto &R:C) for(auto &v:R) v/=size*size;
        return dst;
    }




    const Matrix &AbstractMeanBlurFilter::getKernel(int size) {
        if(!kernels.count(size))
        {
            Matrix kernel(0,linalg::m_shape{size,size});
            for(int i=0;i<size;i++) for(int j=0;j<size;j++)
                    kernel[i][j]=1.0/(size*size);
            kernels[size]=kernel;
        }
        return kernels[size];
    }

    AbstractMeanBlurFilter::AbstractMeanBlurFilter(int size):size(size) {

    }

    const Matrix &AbstractMeanBlurFilter::getKernel() const {
        return getKernel(size);
    }

    Real AbstractMeanBlurFilter::getComponent(int x, int y) const {
        return 1.L/(size*size);
    }

    [[deprecated("Not properly defined")]]
    Image MeanBlurFilter::apply(const Image &src) const {

        for(auto &channel : src.data)
        {
            tensor<2> prefixSum = make_tensor(src.width,src.height);
            for(int i=0;i<src.width;i++) {
                prefixSum[i][0] = channel[i][0];
                for (int j = 0; j < src.height; j++)
                    prefixSum[i][j] = prefixSum[i][j - 1] + channel[i][j];
            }
            for(int i=1;i<src.width;i++) for(int j=0;j<src.height;j++)
                    prefixSum[i][j] += prefixSum[i-1][j];
        }
        return src;
    }

    Image MeanBlurFilter::apply(Padding &src) const
    {
        Image dst(src.image().width,src.image().height,src.image().nb_channel);
        int s1=size/2,s2=size/2;
        for(int c=0;c<src.image().nb_channel;c++)
        {
            tensor<2> prefixSum = make_tensor(src.image().width+size+1,src.image().height+size+1);
            for(int i=1;i<=src.image().width+size;i++) {
                for (int j = 1; j <= src.image().height+size; j++)
                    prefixSum[i][j] = prefixSum[i][j - 1] + src(c,i-s1-1,j-s2-1);
            }
            for(int i=1;i<=src.image().width+size;i++) for(int j=0;j<=src.image().height+size;j++)
                    prefixSum[i][j] += prefixSum[i-1][j];
            for(int i=s1+1;i<=src.image().width+s1;i++) for(int j=s2+1;j<=src.image().height+s2;j++)
                    dst(c,i-1-s1,j-1-s2) = (prefixSum[i+s1][j+s2] - prefixSum[i+s1][j-s2-1] - prefixSum[i-s1-1][j+s2] + prefixSum[i-s1-1][j-s2-1])/(size*size);
        }
        return dst;
    }
} // filter