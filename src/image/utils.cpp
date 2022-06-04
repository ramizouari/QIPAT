//
// Created by ramizouari on 02/05/22.
//
#include <memory>
#include "utils.h"
#include "functional/zip.h"
#include "functional/functional.h"

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


        Image imageLogSpectrum(const Image& src, int max_value)
        {
            Image dst(src.width,src.height,src.nb_channel,max_value);
            for(auto [C,D]: functional::zip(src.data,dst.data))
            {
                auto shape=linalg::m_shape{(int)src.width,(int)src.height};
                fft::multidimensional_fft<2> fft(shape.n,shape.m);
                linalg::d_matrix<algebra::IC> P(0,shape);
                int i=0,j=0;
                for(auto [R1,R2]:functional::zip(P,C)){
                    for(auto [x,y]:functional::zip(R1,R2))
                        x=y;
                }
                auto spectrum=fft((fft::tensor<2,algebra::IC>&)P);
                for(auto [R1,R2]:functional::zip(spectrum,D)) for(auto [x,y]:functional::zip(R1,R2))
                        y=std::log(1+std::sqrt(std::pow(x.real(),2)+std::pow(x.imag(),2)));
                Real E=0;
                for (auto &R: D)
                    for (auto &P: R)
                        E=std::max(E,P);
                functional::apply_pointwise([E,max_value](auto x){ return max_value*x/E;},D);
            }
            return phaseTransform(dst);
        }


        Image imageEnergySpectrum(const Image& src, int max_value)
        {
            Image dst(src.width,src.height,src.nb_channel,max_value);
            auto spectrum= imageToSpectrum(src);
            for(auto [C,D]: functional::zip(spectrum,dst.data))
            {
                for(auto [R1,R2]:functional::zip(C,D)) for(auto [x,y]:functional::zip(R1,R2))
                        y=std::pow(x.real(),2)+std::pow(x.imag(),2);

            }
            return phaseTransform(dst);
        }

        Image phaseTransform(const Image &src) {
            image::Image I(src.width,src.height,src.nb_channel);
            for(int c=0;c<I.nb_channel;c++)
                for(int i=0;i<I.width;i++) for(int j=0;j<I.height;j++)
                    {
                        if(i< I.width/2 && j< I.height/2)
                            I(c,i+I.width/2,j+I.height/2)=src(c,i,j);
                        else if(i>= I.width/2 && j< I.height/2)
                            I(c,i-I.width/2,j+I.height/2)=src(c,i,j);
                        else if(i< I.width/2 && j>= I.height/2)
                            I(c,i+I.width/2,j-I.height/2)=src(c,i,j);
                        else
                            I(c,i-I.width/2,j-I.height/2)=src(c,i,j);
                    }
            return I;
        }

        Image phaseInverseTransform(const Image &src) {
            image::Image I(src.width,src.height,src.nb_channel);
            for(int c=0;c<I.nb_channel;c++)
                for(int i=0;i<I.width;i++) for(int j=0;j<I.height;j++)
                    {
                        if(i< I.width/2 && j< I.height/2)
                            I(c,i,j)=src(c,i+I.width/2,j+I.height/2);
                        else if(i>= I.width/2 && j< I.height/2)
                            I(c,i,j)=src(c,i-I.width/2,j+I.height/2);
                        else if(i< I.width/2 && j>= I.height/2)
                            I(c,i,j)=src(c,i+I.width/2,j-I.height/2);
                        else
                            I(c,i,j)=src(c,i-I.width/2,j-I.height/2);
                    }
            return I;
        }

        Matrix phaseTransform(const Matrix &src) {
            Matrix I(0,linalg::m_shape{(int)src.row_dim(),(int)src.col_dim()});
            int width=src.row_dim();
            int height=src.col_dim();
            for(int i=0;i<I.row_dim();i++) for(int j=0;j<I.col_dim();j++)
                {
                    if(i< width/2 && j< height/2)
                        I[i+width/2][j+height/2]=src[i][j];
                    else if(i>= width/2 && j< height/2)
                        I[i-width/2][j+height/2]=src[i][j];
                    else if(i< width/2 && j>= height/2)
                        I[i+width/2][j-height/2]=src[i][j];
                    else
                        I[i-width/2][j-height/2]=src[i][j];
                }
            return I;
        }
        Matrix phaseInverseTransform(const Matrix &src) {
            Matrix I(0,linalg::m_shape{(int)src.row_dim(),(int)src.col_dim()});
            int width=src.row_dim();
            int height=src.col_dim();
            for(int i=0;i<I.row_dim();i++) for(int j=0;j<I.col_dim();j++)
                {
                    if(i< width/2 && j< height/2)
                        I[i][j]=src[i+width/2][j+height/2];
                    else if(i>= width/2 && j< height/2)
                        I[i][j]=src[i-width/2][j+height/2];
                    else if(i< width/2 && j>= height/2)
                        I[i][j]=src[i+width/2][j-height/2];
                    else
                        I[i][j]=src[i-width/2][j-height/2];
                }
            return I;
        }

        tensor_t<Complex, 3>::tensor imageToSpectrum(const Image &src) {
            tensor_t<Complex,3>::tensor dst=tensor_t<Complex,3>::tensor(
                    src.nb_channel,tensor_t<Complex,2>::tensor (src.width,tensor_t<Complex,1>::tensor (src.height))
                    );
            for(auto [C,D]: functional::zip(src.data,dst))
            {
                auto shape=linalg::m_shape{(int)src.width,(int)src.height};
                fft::multidimensional_fft<2> fft(shape.n,shape.m);
                linalg::d_matrix<algebra::IC> P(0,shape);
                int i=0,j=0;
                for(auto [R1,R2]:functional::zip(P,C)){
                    for(auto [x,y]:functional::zip(R1,R2))
                        x=y;
                }
                auto spectrum=fft((fft::tensor<2,algebra::IC>&)P);
                for(auto [R1,R2]:functional::zip(spectrum,D)) for(auto [x,y]:functional::zip(R1,R2))
                        y=x;
            }
            return dst;
        }

        Image spectrumToImage(const tensor_t<Complex,3>::tensor &src) {
            Image dst(src.front().size(),src.front().front().size(),src.size());
            for(auto [C,D]: functional::zip(src,dst.data))
            {
                auto shape=linalg::m_shape{(int)dst.width,(int)dst.height};
                fft::multidimensional_fft<2,true> ifft(shape.n,shape.m);
                auto image=ifft(C);
                for(auto [R1,R2]:functional::zip(image,D)) for(auto [x,y]:functional::zip(R1,R2))
                        y=std::clamp<Real>(x.real()/(shape.n*shape.m),0,255);
            }
            return dst;
        }

        std::pair<Image, Image> spectrumToImagePair(const tensor_t<Complex,3>::tensor &src) {
            int width=src.front().size();
            int height=src.front().front().size();
            int nb_channel=src.size();
            Image I1(width,height,nb_channel);
            Image I2(width,height,nb_channel);
            for(auto [A,B,C] : functional::zip(src,I1.data,I2.data))
                for(auto [R1,R2,R3]:functional::zip(A,B,C))
                    for(auto [x,y,z]:functional::zip(R1,R2,R3))
                        {
                            y=x.real();
                            z=x.imag();
                        }
            return std::make_pair(I1,I2);
        }

        tensor_t<Complex,3>::tensor imagePairToSpectrum(const std::pair<Image,Image> &P)
        {
            int width=P.first.width;
            int height=P.first.height;
            int nb_channel=P.first.nb_channel;
            tensor_t<Complex,3>::tensor dst(nb_channel,tensor_t<Complex,2>::tensor (width,tensor_t<Complex,1>::tensor (height)));
            for(auto [A,B,C] : functional::zip(P.first.data,P.second.data,dst))
                for(auto [R1,R2,R3]:functional::zip(A,B,C))
                    for(auto [x,y,z]:functional::zip(R1,R2,R3))
                        z=x+y*algebra::IC(0,1);

            return dst;
        }

        tensor_t<Complex, 3>::tensor imagePairToSpectrum(const Image &A, const Image &B) {
            return imagePairToSpectrum(std::make_pair(std::cref(A),std::cref(B)));
        }
    }




    Matrix as_matrix(const Image& src,int channel)
    {
        Matrix dst(0,linalg::m_shape{src.width,src.height});
        for(auto [R1,R2]:functional::zip(src.data[channel],dst))
            std::copy(R1.begin(),R1.end(),R2.begin());
        return dst;
    }

    Matrix as_matrix(Image&& src,int channel)
    {
        Matrix dst(0,linalg::m_shape{src.width,src.height});
        for(auto [R1,R2]:functional::zip(src.data[channel],dst))
            std::move(R1.begin(),R1.end(),R2.begin());
        return dst;
    }


    Image crop(const Image& src,int x,int y,int w,int h)
    {
        Image dst(w,h,src.nb_channel);
        for(auto [C,D]:functional::zip(src.data,dst.data))
            for(int i=0;i<w;i++) for(int j=0;j<h;j++)
                D[i][j]=C[x+i][y+j];
        return dst;
    }




}

std::unique_ptr<nt::factoriser> F = std::make_unique<nt::factoriser>(image::factorisation::LIMIT);
[[maybe_unused]] nt::factoriser& image::factorisation::factoriser{*F};