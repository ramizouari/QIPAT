//
// Created by ramizouari on 02/05/22.
//

#ifndef IMAGEPROCESSING_UTILS_H
#define IMAGEPROCESSING_UTILS_H
#include "stats.h"
#include "nt/number_theory.h"
#include "polynomial/fft.h"

namespace image
{
    template<typename G>
    concept RealMatrixGenerator = requires(G r, int w, int h)
    {
        {r(w, h)} -> std::same_as<Real>;
    };

    template<typename G>
    concept RealArrayGenerator = requires(G r, int x)
    {
        {r(x)} -> std::same_as<Real>;
    };


    template <RealMatrixGenerator Generator>
    Matrix generateMatrix(int w, int h,const Generator &generator)
    {
        Matrix M(0,linalg::m_shape{w,h});
        for(int i=0;i<w;i++)
            for(int j=0;j<h;j++)
                M[i][j]=generator(i,j);
        return M;
    }


    Image histogramEqualization(const Image& src);
    namespace factorisation
    {
        constexpr int LIMIT = 1e6;
        [[maybe_unused]] [[maybe_unused]] extern nt::factoriser& factoriser;
    }

    namespace convolution
    {
        Image resizeKernel(const Image& kernel, int new_w, int new_h,int p,int q);
        Matrix resizeKernel(const Matrix& kernel, int new_w, int new_h,int p,int q);
        Image resizeKernel(const Image& kernel, int new_w, int new_h);
        Matrix resizeKernel(const Matrix& kernel, int new_w, int new_h);
        Matrix fast_convolution(const Matrix& src, const Matrix& kernel);
        Image fast_convolution(const Image& src, const Matrix& kernel);
        Image fast_convolution(const Image& src, const Image& kernel);

        Image imageLogSpectrum(const Image& src, int max_value=255);
        Image imageEnergySpectrum(const Image& src, int max_value=255);
        Image phaseTransform(const Image& src);
        Image phaseInverseTransform(const Image &src);
        Matrix phaseTransform(const Matrix& src);
        Matrix phaseInverseTransform(const Matrix &src);
        Image fftTransform(const Image& src);
    }

    [[maybe_unused]] Matrix as_matrix(const Image& src,int channel=0);
    [[maybe_unused]] Matrix as_matrix(Image &&src,int channel=0);
    Image crop(const Image& src,int x,int y,int w,int h);
}


#endif //IMAGEPROCESSING_UTILS_H
