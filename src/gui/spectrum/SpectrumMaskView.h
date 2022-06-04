//
// Created by ramizouari on 14/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMMASKVIEW_H
#define IMAGEPROCESSING_SPECTRUMMASKVIEW_H

#include "SpectrumView.h"

namespace GUI::spectrum {

        class SpectrumMaskView: public ImageView {
            std::unique_ptr<image::Image> energySpectrum;
            std::vector<std::vector<bool>> mask;
            image::Real totalEnergy,remainingEnergy;
        public:
            explicit SpectrumMaskView(const image::Image & img, QWidget *parent = nullptr);
            void setImage(const image::Image &img);
            void setImage(const image::Image &img,const std::vector<std::vector<bool>> &mask);
            void setSpectrum(const image::Image &img);
            void setSpectrum(image::Image &&img);
            void setMask(const std::vector<std::vector<bool>> &mask,bool invert=false);
            image::Image& getSpectrum() const;
            [[nodiscard]] image::Real getTotalEnergy() const;
            [[nodiscard]] image::Real getRemainingEnergy() const;
            [[nodiscard]] const std::vector<std::vector<bool>> & getMask() const;
        };

    } // spectrum

#endif //IMAGEPROCESSING_SPECTRUMMASKVIEW_H
