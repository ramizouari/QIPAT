//
// Created by ramizouari on 03/05/22.
//

#include "LaplacianOperator.h"

namespace image::filter::differential
{
    Matrix LaplacianOperator::kernel{Matrix({{0, 1, 0}, {1, -4, 1}, {0, 1, 0}})};

    const Matrix &LaplacianOperator::getKernel() const {
        return kernel;
    }

    [[deprecated("Not defined")]]
    Image LaplacianOperator::apply(const Image &src) const {
        return Image(0, 0);
    }

    Image LaplacianOperator::apply(Padding &src) const {
        Image dst(src.image().width,src.image().height,src.image().nb_channel,src.image().max);
        for(int c=0;c<src.image().nb_channel;c++) for(int i=0;i<src.image().width;i++) for(int j=0;j<src.image().height;j++)
                    dst.data[c][i][j]=std::clamp<Real>(-4*src(c,i,j)+src(c,i+1,j)+src(c,i-1,j)+src(c,i,j+1)+src(c,i,j-1),0,dst.max);
        return dst;
    }

    Real LaplacianOperator::getComponent(int i,int j) const {
        return kernel[i][j];
    }

    Matrix LaplacianOperatorWithDiagonal::kernel{Matrix({{.5, 1, .5}, {1, -6, 1}, {.5, 1, .5}})};

    const Matrix &LaplacianOperatorWithDiagonal::getKernel() const {
        return kernel;
    }

    [[deprecated("Not defined")]]
    Image LaplacianOperatorWithDiagonal::apply(const Image &src) const {
        return Image(0, 0);
    }

    Image LaplacianOperatorWithDiagonal::apply(Padding &src) const {
        Image dst(src.image().width,src.image().height,src.image().nb_channel,src.image().max);
        for(int c=0;c<src.image().nb_channel;c++) for(int i=0;i<src.image().width;i++) for(int j=0;j<src.image().height;j++)
                    dst.data[c][i][j]=std::clamp<Real>(-4*src(c,i,j)+src(c,i+1,j)+src(c,i-1,j)+src(c,i,j+1)+src(c,i,j-1),0,dst.max);
        return dst;
    }

    Real LaplacianOperatorWithDiagonal::getComponent(int i, int j) const {
        return kernel[i][j];
    }
} // differential