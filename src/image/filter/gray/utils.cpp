//
// Created by ramizouari on 02/05/22.
//

#include <memory>
#include "utils.h"
#include "MaxChannelFilter.h"
#include "MeanChannelFilter.h"
#include "L1NormChannelFilter.h"
#include "L2NormChannelFilter.h"

namespace image::filter::gray
{
    std::unique_ptr<GrayFilter> maxChannelFilterPtr = std::make_unique<MaxChannelFilter>(),
            meanChannelFilterPtr = std::make_unique<MeanChannelFilter>(),
            rec709FilterPtr = std::make_unique<MeanChannelFilter>(0.2126, 0.7152, 0.0722),
            rec601FilterPtr = std::make_unique<MeanChannelFilter>(0.299, 0.587, 0.114),
            l1NormFilterPtr = std::make_unique<L1NormChannelFilter>(),
            l2NormFilterPtr = std::make_unique<L2NormChannelFilter>();

    GrayFilter & maxChannelFilter=*maxChannelFilterPtr;
    GrayFilter & meanChannelFilter=*meanChannelFilterPtr;
    GrayFilter & rec709Filter=*rec709FilterPtr;
    GrayFilter & rec601Filter=*rec601FilterPtr;
    GrayFilter & l1NormFilter=*l1NormFilterPtr;
    GrayFilter & l2NormFilter=*l2NormFilterPtr;
}