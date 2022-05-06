//
// Created by ramizouari on 02/05/22.
//

#include "SobelOperator.h"
#include "functional/zip.h"

namespace image::filter::differential {
    ConvolutionalFilter SobelOperator::Gx{Matrix({{1, 0, -1}, {2, 0, -2}, {1, 0, -1}})};
    ConvolutionalFilter SobelOperator::Gy{Matrix({{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}})};
    Image SobelOperator::apply(const Image &src) const
    {
        auto X=Gx.apply(src),Y=Gy.apply(src);
        Image Z(X.width,X.height,X.nb_channel);
        for(auto [C1,C2,C3]:functional::zip(X.data,Y.data,Z.data)) for(auto [R1,R2,R3]: functional::zip(C1,C2,C3)) for(auto [x,y,z]:functional::zip(R1,R2,R3))
                    z=std::clamp<Real>(std::sqrt(x*x+y*y),0,src.max);
        return Z;
    }

    Image SobelOperator::apply(Padding &src) const {
        auto X=Gx.apply(src),Y=Gy.apply(src);
        Image Z(X.width,X.height,X.nb_channel);
        for(auto [C1,C2,C3]:functional::zip(X.data,Y.data,Z.data)) for(auto [R1,R2,R3]: functional::zip(C1,C2,C3)) for(auto [x,y,z]:functional::zip(R1,R2,R3))
                    z=std::clamp<Real>(std::sqrt(x*x+y*y),0,src.image().max);
        return Z;
    }

} // differential