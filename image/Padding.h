//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_PADDING_H
#define IMAGEPROCESSING_PADDING_H


#include "Image.h"

namespace image
{
    class Padding
    {
    protected:
        Image* imagePtr;
    public:
        explicit Padding(Image &image);
        virtual ~Padding() = default;
        Real operator()(int x, int y) const;
        virtual Real operator()(int c,int x, int y) const = 0;
        [[nodiscard]] Image& image() const;
        void setImage(Image &image);
    };

    class ConstantPadding : public Padding
    {
        Real value;
    public:
        ConstantPadding(Image &image, Real value);
        Real operator()(int c,int x, int y) const override;
    };

    class ZeroPadding : public ConstantPadding
    {
    public:
        explicit ZeroPadding(Image &image);
    };

    class SymmetricPadding : public Padding {
    public:
        using Padding::Padding;
        Real operator()(int c,int x, int y) const override;
    };

    class TranslationalPadding : public Padding {
    public:
        using Padding::Padding;
        Real operator()(int c,int x, int y) const override;
    };
}


#endif //IMAGEPROCESSING_PADDING_H
