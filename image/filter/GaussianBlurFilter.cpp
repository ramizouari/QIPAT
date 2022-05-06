//
// Created by ramizouari on 06/05/22.
//

#include "GaussianBlurFilter.h"

namespace image::filter {
        std::pair<Vector, Vector> GaussianBlurFilter::getKernels(Real stdX,Real stdY,int stdCount)
        {
            auto dimX=static_cast<int>(std::ceil(stdX*stdCount));
            auto dimY=static_cast<int>(std::ceil(stdY*stdCount));
            Vector K1(linalg::v_shape{2*dimX+1}),K2(linalg::v_shape{2*dimY+1});
            for(int i=-dimX;i<=dimX;i++)
                K1[i+dimX]= stdX==0?i==0:std::exp(-i*i/(2*stdX*stdX));
            K1/=std::reduce(K1.begin(),K1.end());
            for(int i=-dimY;i<=dimY;i++)
                K2[i+dimY]= stdY==0?i==0:std::exp(-i*i/(2*stdY*stdY));
            K2/=std::reduce(K2.begin(),K2.end());
            return std::make_pair(K1,K2);
        }

    GaussianBlurFilter::GaussianBlurFilter(Real stdX, Real stdY, int stdCount):
            stdX(stdX),stdY(stdY),stdCount(stdCount)
    {
            std::tie(K1,K2)=getKernels(stdX,stdY,stdCount);
    }

    GaussianBlurFilter::GaussianBlurFilter(Real std, int stdCount):stdCount(stdCount),stdX(std),stdY(std){
        std::tie(K1,K2)=getKernels(std,std,stdCount);
    }
} // filter