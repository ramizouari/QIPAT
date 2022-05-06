//
// Created by ramizouari on 01/05/22.
//

#include <cmath>
#include "Filter.h"
#include "data_structures/statistic_tree.h"
#include "numeric"


namespace image::filter {
    Image Filter::operator()(const Image &src) const {
        return apply(src);
    }

    void Filter::operator()(const Image&src,  Image& dst) const {
        apply(src);
    }

    void Filter::apply(const Image &src, Image &dst) const {
        dst=std::move(apply(src));
    }




} // image