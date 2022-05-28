//
// Created by ramizouari on 30/04/22.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H
#include <vector>
#include <span>
#include "linear_algebra/linear_algebra.h"


namespace image
{
    template<typename T,int n>
    struct tensor_t
    {
        using tensor = std::vector<typename tensor_t<T,n-1>::tensor>;
    };

    template<typename T>
    struct tensor_t<T,0>
    {
        using tensor = T;
    };

    using Real = linalg::real;
    using Complex=linalg::IC;
    using Integer=algebra::integer;
    using Vector=linalg::d_vector<Real>;
    using Vectori=linalg::d_vector<Integer>;
    using Vector2 = linalg::s_vector<Real,2>;
    using Vector3 = linalg::s_vector<Real,3>;
    using Vector4 = linalg::s_vector<Real,4>;
    using Vector5 = linalg::s_vector<Real,5>;
    using Vector2i = linalg::s_vector<Integer,2>;
    using Vector3i = linalg::s_vector<Integer,3>;
    using Vector4i = linalg::s_vector<Integer,4>;
    using Vector5i = linalg::s_vector<Integer,5>;
    using Vectorc=linalg::d_vector<Complex>;
    using Vector2c = linalg::s_vector<Complex,2>;
    using Vector3c = linalg::s_vector<Complex,3>;
    using Vector4c = linalg::s_vector<Complex,4>;
    using Vector5c = linalg::s_vector<Complex,5>;
    using Matrix = linalg::d_matrix<Real>;
    using Matrix2 = linalg::s_matrix<Real,2,2>;
    using Matrix3 = linalg::s_matrix<Real,3,3>;
    using Matrix4 = linalg::s_matrix<Real,4,4>;
    using Matrix5 = linalg::s_matrix<Real,5,5>;
    using Matrixi = linalg::d_matrix<Integer>;
    using Matrix2i = linalg::s_matrix<Integer,2,2>;
    using Matrix3i = linalg::s_matrix<Integer,3,3>;
    using Matrix4i = linalg::s_matrix<Integer,4,4>;
    using Matrix5i = linalg::s_matrix<Integer,5,5>;
    using Matrixc = linalg::d_matrix<Complex>;
    using Matrix2c = linalg::s_matrix<Complex,2,2>;
    using Matrix3c = linalg::s_matrix<Complex,3,3>;
    using Matrix4c = linalg::s_matrix<Complex,4,4>;
    using Matrix5c = linalg::s_matrix<Complex,5,5>;
    template<int n>
    using tensor=typename tensor_t<Real,n>::tensor;

    template<int n>
    tensor<n> make_tensor(std::span<unsigned int,n> dims)
    {
        if constexpr (n==1)
            return std::vector<Real>(dims.front());
        else {
            std::span<unsigned int, n - 1> subdim(dims.begin() + 1, n - 1);
            return std::vector<tensor<n - 1>>(dims[0], make_tensor<n - 1>(subdim));
        }
    }

    template<int n>
    tensor<n> make_tensor(std::array<unsigned int,n> dims)
    {
        return make_tensor<n>(std::span(dims));
    }

    template <typename ...T>
    tensor<sizeof...(T)> make_tensor(T... dimensions)
    {
        std::array<unsigned int,sizeof...(T)> dims{static_cast<unsigned int>(dimensions)...};
        return make_tensor<sizeof...(T)>(dims);
    }

    class Image
    {
    protected:

        void update_parameters();
        inline static constexpr int MAX=255;
    public:
        Image(int width, int height, int nb_channel=1,int max=MAX);
        Image(const Image& other);
        Image(Image&& other) noexcept ;
        explicit Image(tensor<2> &other,int max=MAX);
        explicit Image(tensor<2> &&other,int max=MAX) noexcept;
        explicit Image(tensor<3> &other,int max=MAX);
        explicit Image(tensor<3> &&other,int max=MAX) noexcept;

        Image& operator=(const Image& other);
        Image& operator=(Image&& other) noexcept;
        Image& operator=(const tensor<2>& other);
        Image&operator= (tensor<2>&& other);
        Image& operator=(const tensor<3>& other);
        Image& operator=(tensor<3>&& other);
        unsigned int max;
        ~Image();
        std::vector<std::vector<std::vector<Real>>> data;
        int width;
        int height;
        int nb_channel;
        Real& operator()(int i,int j,int k);
        const Real& operator()(int i,int j,int k) const;
        Real& operator()(int i,int j);
        const Real& operator()(int i,int j) const;
    };

    class MonoImage: public Image{
    public:
        MonoImage(int width, int height, int max=MAX);
        MonoImage(const MonoImage& other);
        MonoImage(MonoImage&& other) noexcept ;
        ~MonoImage();
        auto& operator[](int i);
        const auto& operator[](int i) const;

    };

    class PolyImage : public Image
    {
    protected:
        int width;
        int height;
        int nb_channel;
        std::vector<std::vector<std::vector<Real>>> data;
    public:
        using Image::Image;
        auto& operator[](int i);
        const auto& operator[](int i) const;
    };
}

#endif //IMAGEPROCESSING_IMAGEREADER_H
