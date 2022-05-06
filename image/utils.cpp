//
// Created by ramizouari on 02/05/22.
//
#include <memory>
#include "utils.h"
#include "functional/zip.h"

namespace image
{

    Image histogramEqualization(const Image &src) {
        Image dst(src.width, src.height, src.nb_channel);
        auto hists=stats::cumulativeHistogram(src,true);
        std::vector<unsigned int> mapping(src.max+1);
        for(int c=0;c<src.nb_channel;c++)
        {
            auto &H=hists[c];
            int s=0;
            for(int i=0;i<H.size();i++){
                H[i] *= src.max;
                mapping[i]=std::floor(H[i]);
            }
            for(int i=0;i<dst.width;i++) for(int j=0;j<dst.height;j++)
                dst.data[c][i][j]=mapping[std::floor(src.data[c][i][j])];
        }
        return dst;
    }

    namespace convolution
    {
        Matrix fast_convolution(const Matrix& src, const Matrix& kernel)
        {
            auto shape=linalg::m_shape{(int)src.row_dim(),(int)src.col_dim()};
            fft::multidimensional_fft<2> fft(shape.n,shape.m);
            fft::multidimensional_fft<2,true> inverse_fft(shape.n,shape.m);
            linalg::d_matrix<algebra::IC> P(0,shape);
            linalg::d_matrix<algebra::IC> Q(0,shape);
            for(auto [R1,R2]:functional::zip(P,src)) for(auto [x,y]:functional::zip(R1,R2))
                x=y;
            auto X=fft((fft::tensor<2,linalg::IC>&)P);
            auto &Y=kernel;
            /*
             * Possible because they are really the same type, but the compiler was not able to prove it
             * */
            fft::tensor<2,algebra::IC> Z(shape.n,fft::tensor<1,algebra::IC>(shape.m));
            for(auto [R1,R2,R3]:functional::zip(X,Y,Z)) for(auto [x,y,z]:functional::zip(R1,R2,R3))
                    z=x*y;
            auto U=inverse_fft(Z);
            Matrix V(0,shape);
            for(auto [R1,R2]: functional::zip(U,V)) for(auto [u,v]:functional::zip(R1,R2))
                    v=u.real();
            return V;
        }
        Image fast_convolution(const Image& src, const Matrix& kernel)
        {
            Image dst(src.width,src.height,src.nb_channel);
            for(auto [C,D]:functional::zip(src.data,dst.data))
            {
                auto K=fast_convolution(C,kernel);
                std::move(K.begin(),K.end(),D.begin());
            }
            return dst;
        }
        Image fast_convolution(const Image& src, const Image& kernel)
        {
            Image dst(src.width,src.height,src.nb_channel),resizedKernel=resizeKernel(kernel,src.width,src.height,src.width/2,src.height/2);
            for(auto [A,B,C]:functional::zip(src.data,resizedKernel.data,dst.data))
            {
                auto K=fast_convolution(A,B);
                C=reinterpret_cast<fft::tensor<2,Real>&&>(std::move(K));
            }
            return dst;
        }

        Image resizeKernel(const Image& kernel, int new_w, int new_h,int p,int q)
        {
            Image dst(new_w,new_h,kernel.nb_channel);
            for(int c=0;c<kernel.nb_channel;c++) for(int i=0;i<kernel.width;i++) for(int j=0;j<kernel.height;j++)
                dst(c,i-kernel.width/2+p,j-kernel.height/2+q)=kernel(c,i,j);
            return dst;
        }

        Matrix resizeKernel(const Matrix& kernel, int new_w, int new_h,int p,int q)
        {
            Matrix dst(0,linalg::m_shape{new_w,new_h});
            for(int i=0;i<kernel.row_dim();i++) for(int j=0;j<kernel.col_dim();j++)
                dst[i-kernel.row_dim()/2+p][j-kernel.col_dim()/2+q]=kernel[i][j];
            return dst;
        }

        Image resizeKernel(const Image& kernel, int new_w, int new_h)
        {
            Image dst(new_w,new_h,kernel.nb_channel);
            for(int c=0;c<kernel.nb_channel;c++) for(int i=0;i<kernel.width;i++) for(int j=0;j<kernel.height;j++)
                        dst(c,i,j)=kernel(c,i,j);
            return dst;
        }
        Matrix resizeKernel(const Matrix& kernel, int new_w, int new_h)
        {
            Matrix dst(0,linalg::m_shape{new_w,new_h});
            for(int i=0;i<kernel.row_dim();i++) for(int j=0;j<kernel.col_dim();j++)
                    dst[i][j]=kernel[i][j];
            return dst;
        }
    }

}

std::unique_ptr<nt::factoriser> F = std::make_unique<nt::factoriser>(image::factorisation::LIMIT);
[[maybe_unused]] nt::factoriser& image::factorisation::factoriser{*F};