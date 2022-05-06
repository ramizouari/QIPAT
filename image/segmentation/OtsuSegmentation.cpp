//
// Created by ramizouari on 05/05/22.
//

#include <queue>
#include "OtsuSegmentation.h"
#include "image/stats.h"

namespace image::segmentation {
        OtsuSegmentation::OtsuSegmentation() = default;

    Image OtsuSegmentation::apply(const Image &src) const {
        auto dst=src;
        auto Hs=image::stats::histogram(src);
        std::vector<int> thresholds;
        for(const auto& H:Hs) {
            auto cumulativeHist = H;
            auto cdf2 = H;
            auto cdf = H;
            for (int i = 1; i < cdf2.size(); i++) {
                cdf2[i] *= i * i;
                cdf[i] *= i;
                cdf[i] += cdf[i - 1];
                cdf2[i] += cdf2[i - 1];
                cumulativeHist[i] += cumulativeHist[i - 1];
            }
            auto colors = H.size();
            Real V_inf = std::numeric_limits<Real>::infinity();
            int threshold = 0;
            for (int i = 0; i < colors - 1; i++) {
                auto V1 = (cumulativeHist[i] * cdf2[i] - std::pow(cdf[i], 2));
                auto V2 = ((cumulativeHist[colors - 1] - cumulativeHist[i]) * (cdf2[colors - 1] - cdf2[i]) -
                           std::pow(cdf[colors - 1] - cdf[i], 2));
                if (V1 + V2 < V_inf) {
                    V_inf = V1 + V2;
                    threshold = i;
                }
            }
            thresholds.push_back(threshold);
        }
        for(int i=0;i<dst.nb_channel;i++) for(auto &R:dst.data[i]) for(auto &p:R)
        {
            if(p<=thresholds[i]) p=0;
            else p=1;
        }
        dst.max=1;
        return dst;
    }

    IterativeOtsuSegmentation::IterativeOtsuSegmentation(int _k):k(_k) {

    }

    Image IterativeOtsuSegmentation::apply(const Image &src) const {
        auto dst=src;
        auto Hs=image::stats::histogram(src);
        std::vector<std::vector<int>> thresholds;
        for (int c=0;c<dst.nb_channel;c++)
    {
            auto &H=Hs[c];
            auto cumulativeHist = H;
            auto cdf2 = H;
            auto cdf = H;
            for (int i = 1; i < cdf2.size(); i++)
            {
                cdf2[i] *= i * i;
                cdf[i] *= i;
                cdf[i] += cdf[i - 1];
                cdf2[i] += cdf2[i - 1];
                cumulativeHist[i] += cumulativeHist[i - 1];
            }
            auto colors = H.size();
            using triplet = std::tuple<Real,int,int>;
            std::priority_queue<triplet> V;
            thresholds.emplace_back();
            auto &threshold = thresholds.back();
            V.emplace(0,0,H.size());
            int r = k;
            while (r-- >= 2) {
                Real V_inf = std::numeric_limits<Real>::infinity();
                auto [_,t1,t2] = V.top();
                V.pop();
                Real lastCumulativeHist = t1==0?0:cumulativeHist[t1-1], lastCdf2 = t1==0?0:cdf2[t1-1], lastCdf = t1==0?0:cdf[t1-1];
                int index = 0;
                Real R1,R2;
                for (int i = t1+1; i < t2; i++)
                {
                    Real V1 = ((cumulativeHist[i - 1] - lastCumulativeHist) * (cdf2[i - 1] - lastCdf2) -
                               std::pow(cdf[i - 1] - lastCdf, 2));
                    Real V2 = ((cumulativeHist[t2 - 1] - cumulativeHist[i - 1]) *
                               (cdf2[t2 - 1] - cdf2[i - 1]) -
                               std::pow(cdf[t2 - 1] - cdf[i - 1], 2));
                    if (V1 + V2 < V_inf) {
                        index=i;
                        V_inf = V1 + V2;

                        R1=V1;
                        R2=V2;

                    }
                }
                  V.emplace(R1,t1,index);
                V.emplace(R2,index,t2);
                thresholds.back().push_back(index);
            }
        }

        for(int i=0;i<dst.nb_channel;i++) for(auto &R:dst.data[i]) for(auto &p:R)
        {
            p=std::upper_bound(thresholds[i].begin(),thresholds[i].end(),p)-thresholds[i].begin();
            p*=dst.max;
            p/=thresholds[i].size();
        }
        return dst;
    }

} // segmentation