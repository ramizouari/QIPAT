//
// Created by ramizouari on 03/05/22.
//

#include "RobertsOperator.h"
#include "functional/zip.h"

namespace image::filter::differential
{
    ConvolutionalFilter RobertsOperator::Gx{Matrix({{0,-1},{1,0}})};
    ConvolutionalFilter RobertsOperator::Gy{Matrix({{-1,0},{0,1}})};
    Image RobertsOperator::apply(const Image &src) const
    {
        auto X=Gx.apply(src),Y=Gy.apply(src);
        Image Z(X.width,X.height,X.nb_channel);
        for(auto [C1,C2,C3]:functional::zip(X.data,Y.data,Z.data)) for(auto [R1,R2,R3]: functional::zip(C1,C2,C3)) for(auto [x,y,z]:functional::zip(R1,R2,R3))
                    z=std::clamp<Real>(std::sqrt(x*x+y*y),0,src.max);
        return Z;
    }

    Image RobertsOperator::apply(Padding &src) const {
        auto X=Gx.apply(src),Y=Gy.apply(src);
        Image Z(X.width,X.height,X.nb_channel);
        for(auto [C1,C2,C3]:functional::zip(X.data,Y.data,Z.data)) for(auto [R1,R2,R3]: functional::zip(C1,C2,C3)) for(auto [x,y,z]:functional::zip(R1,R2,R3))
                    z=std::clamp<Real>(std::sqrt(x*x+y*y),0,src.image().max);
        return Z;
    }

} // differential