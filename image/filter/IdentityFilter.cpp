//
// Created by ramizouari on 02/05/22.
//

#include "IdentityFilter.h"

namespace image::filter {

    Image IdentityFilter::apply(const Image &src) const {
        return src;
    }

    Image IdentityFilter::apply(const Padding &src) const {
        return src.image;
    }

    const Matrix &IdentityFilter::getKernel() const {
        static Matrix kernel(1,linalg::m_shape{1,1});
        return kernel;
    }

    Real IdentityFilter::getComponent(int x, int y) const {
        return x==0 && y==0 ? 1 : 0;
    }

} // filter