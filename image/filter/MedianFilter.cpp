//
// Created by ramizouari on 02/05/22.
//

#include "MedianFilter.h"
#include "data_structures/statistic_tree.h"
#include <execution>
#include <future>
#include "utility.h"

namespace image::filter {
    Image MedianFilter::apply(const Padding &src) const
    {
        int L=src.image.width/utility::SOFT_CONCURRENCY_LIMIT;
        Image dst(src.image.width,src.image.height,src.image.nb_channel);
        int s1=size/2,s2=size/2;
        std::vector<int> I(src.image.width);
        std::iota(I.begin(),I.end(),0);
        std::vector<std::future<void>> fut;
        for(int c=0;c<src.image.nb_channel;c++)
        {
            //dst(c,i,j)=median(root)->h;
            for(int r=0;r<utility::SOFT_CONCURRENCY_LIMIT+1;r++)
            fut.emplace_back(std::async([&,r,c]()
            {
                for(int t=0;t<(r==utility::SOFT_CONCURRENCY_LIMIT?src.image.width%utility::SOFT_CONCURRENCY_LIMIT:L);t++) {
                    int i=r*L+t;
                    data_structures::order_node<Real> *root = nullptr;
                    for (int p = 0; p < size; p++)
                        for (int q = 0; q < size; q++)
                            root = data_structures::insert(root, src(c, i + p - s1, q - s2));
                    dst(c, i, 0) = data_structures::median(root)->v;
                    for (int j = 1; j < src.image.height; j++) {
                        for (int p = 0; p < size; p++)
                            root = data_structures::erase(root, src(c, i + p - s1, j - s2 - 1));
                        for (int p = 0; p < size; p++)
                            root = data_structures::insert(root, src(c, i + p - s1, j + s2));
                        dst(c, i, j) = data_structures::median(root)->v;
                    }
                    data_structures::destroy(root);
                }
            }));
        }
        return dst;
    }

    [[deprecated("Not defined")]]
    Image MedianFilter::apply(const Image &src) const {
        return Image(0, 0);
    }

    MedianFilter::MedianFilter(int size) :size(size){}

    SmallMedianFilter::SmallMedianFilter(int size):size(size) {

    }

    Image SmallMedianFilter::apply(const Padding &src) const {
        Image dst(src.image.width,src.image.height,src.image.nb_channel);
        int s1=size/2,s2=size/2;
        for(int c=0;c<src.image.nb_channel;c++) for(int i=0;i<src.image.width;i++) for(int j=0;j<src.image.height;j++)
        {
            std::vector<Real> V;
            for(int p=0;p<size;p++) for(int q=0;q<size;q++)
                V.push_back(src(c,i+p-s1,j+q-s2));
            std::nth_element(V.begin(),V.begin()+V.size()/2,V.end());
            dst(c,i,j)=V[V.size()/2];
        }
        return dst;
    }

    [[deprecated("Not defined")]]
    Image SmallMedianFilter::apply(const Image &src) const {
        return Image(0, 0);
    }

} // filter