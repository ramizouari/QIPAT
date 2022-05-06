//
// Created by ramizouari on 02/05/22.
//

#include "DifferentialFilter.h"
#include "functional/zip.h"

namespace image::filter::differential
{
    Image DifferentialFilter::gradientNorm(const Image &src) const {
        auto dst= apply(src);
        auto &X=dst.data[0], &Y=dst.data[1];
        Image Z(dst.width,dst.height);
        for(auto [R1,R2,R3]: functional::zip(X,Y,Z.data.front())) for(auto [x,y,z]:functional::zip(R1,R2,R3))
            z=std::clamp<Real>(std::sqrt(x*x+y*y),0,src.max);
        return Z;
    }

    Image DifferentialFilter::gradientNorm(const Padding &src) const {
        auto dst= apply(src);
        auto &X=dst.data[0], &Y=dst.data[1];
        Image Z(dst.width,dst.height);
        for(auto [R1,R2,R3]: functional::zip(X,Y,Z.data.front())) for(auto [x,y,z]:functional::zip(R1,R2,R3))
                z=std::clamp<Real>(std::sqrt(x*x+y*y),0,src.image.max);
        return Z;
    }
} // differential