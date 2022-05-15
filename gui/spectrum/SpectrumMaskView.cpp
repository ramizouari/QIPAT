//
// Created by ramizouari on 14/05/22.
//

#include "SpectrumMaskView.h"
#include "image/utils.h"
#include "functional/functional.h"

namespace GUI::spectrum {
        SpectrumMaskView::SpectrumMaskView(const image::Image &img, QWidget *parent): ImageView(parent), mask(img.width, std::vector<bool>(img.height, true)) {
            setImage(img);
        }

    void SpectrumMaskView::setImage(const image::Image &img)
    {
        energySpectrum=std::make_unique<image::Image>(std::move(image::convolution::imageEnergySpectrum(img)));
        auto *newImage=new image::Image(*energySpectrum);
        image::Real E=0;
        totalEnergy=0;
        remainingEnergy=0;
        for(auto &C:newImage->data)
        for (auto &R: C)
            for (auto &P: R) {
                totalEnergy += P;
                P=std::log(std::sqrt(P)+1);
                E = std::max(E, P);
            }
        functional::apply_pointwise([E,max_value=img.max](auto x){ return max_value*x/E;},newImage->data);
        for(int c=0;c<newImage->nb_channel;c++) for(int i=0;i<newImage->width;i++) for(int j=0;j<newImage->width;j++)
            if(!mask[i][j])
                (*newImage)(c,i,j)=0;
            else remainingEnergy+=energySpectrum->data[c][i][j];
        ImageView::setImage(newImage);
    }

    void SpectrumMaskView::setMask(const std::vector<std::vector<bool>> &mask, bool invert) {
            this->mask=mask;
        auto *newImage=new image::Image(*energySpectrum);
        image::Real E=0;
        totalEnergy=0;
        remainingEnergy=0;
        for(auto &C:newImage->data)
            for (auto &R: C)
                for (auto &P: R) {
                    totalEnergy += P;
                    P=std::log(std::sqrt(P)+1);
                    E = std::max(E, P);
                }
        functional::apply_pointwise([E,max_value=energySpectrum->max](auto x){ return max_value * x / E;}, newImage->data);
        for(int c=0;c<newImage->nb_channel;c++) for(int i=0;i<newImage->width;i++) for(int j=0;j<newImage->width;j++)
                    if(mask[i][j]^invert)
                        remainingEnergy+=energySpectrum->data[c][i][j];
                    else newImage->data[c][i][j] = 0;

        ImageView::setImage(newImage);
    }

    void SpectrumMaskView::setImage(const image::Image &img, const std::vector<std::vector<bool>> &_mask) {
        energySpectrum=std::make_unique<image::Image>(std::move(image::convolution::imageEnergySpectrum(img)));
        mask=_mask;
        auto *newImage=new image::Image(*energySpectrum);
        image::Real E=0;
        totalEnergy=0;
        remainingEnergy=0;
        for(auto &C:newImage->data)
            for (auto &R: C)
                for (auto &P: R) {
                    totalEnergy += P;
                    P=std::log(std::sqrt(P)+1);
                    E = std::max(E, P);
                }
        functional::apply_pointwise([E,max_value=img.max](auto x){ return max_value*x/E;},newImage->data);
        for(int c=0;c<newImage->nb_channel;c++) for(int i=0;i<newImage->width;i++) for(int j=0;j<newImage->width;j++)
                    if(!mask[i][j])
                        newImage->data[c][i][j]=0;
                    else remainingEnergy+=energySpectrum->data[c][i][j];

        ImageView::setImage(newImage);
    }

    image::Real SpectrumMaskView::getTotalEnergy() const {
        return totalEnergy;
    }

    image::Real SpectrumMaskView::getRemainingEnergy() const {
        return remainingEnergy;
    }

    const std::vector<std::vector<bool>> &SpectrumMaskView::getMask() const {
        return mask;
    }

    void SpectrumMaskView::setSpectrum(const image::Image &img) {
        energySpectrum=std::make_unique<image::Image>(img);
        auto *newImage=new image::Image(img);
        image::Real E=0;
        totalEnergy=0;
        remainingEnergy=0;
        for(auto &C:newImage->data)
            for (auto &R: C)
                for (auto &P: R) {
                    totalEnergy += P;
                    P=std::log(std::sqrt(P)+1);
                    E = std::max(E, P);
                }
        functional::apply_pointwise([E,max_value=img.max](auto x){ return max_value*x/E;},newImage->data);
        for(int c=0;c<newImage->nb_channel;c++) for(int i=0;i<newImage->width;i++) for(int j=0;j<newImage->width;j++)
            remainingEnergy+=energySpectrum->data[c][i][j];
        ImageView::setImage(newImage);

    }

    image::Image& SpectrumMaskView::getSpectrum() const {
        return *energySpectrum;
    }

    void SpectrumMaskView::setSpectrum(image::Image &&img) {
        energySpectrum=std::make_unique<image::Image>(img);
        auto *newImage=new image::Image(img);
        image::Real E=0;
        totalEnergy=0;
        remainingEnergy=0;
        for(auto &C:newImage->data)
            for (auto &R: C)
                for (auto &P: R) {
                    totalEnergy += P;
                    P=std::log(std::sqrt(P)+1);
                    E = std::max(E, P);
                }
        functional::apply_pointwise([E,max_value=img.max](auto x){ return max_value*x/E;},newImage->data);
        for(int c=0;c<newImage->nb_channel;c++) for(int i=0;i<newImage->width;i++) for(int j=0;j<newImage->width;j++)
                    remainingEnergy+=energySpectrum->data[c][i][j];
        ImageView::setImage(newImage);
    }
} // spectrum