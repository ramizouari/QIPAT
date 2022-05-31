//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMFILTERVIEW_H
#define IMAGEPROCESSING_SPECTRUMFILTERVIEW_H

#include "gui/imageview.h"

namespace GUI::spectrum {

        class SpectrumFilterView :public ImageView {
            Q_OBJECT
            std::unique_ptr<image::Image> energySpectrum;
            std::unique_ptr<image::Image> unfilteredSpectrum;
            image::Real totalEnergy,remainingEnergy;
        public:
            explicit SpectrumFilterView(const image::Image & img, QWidget *parent = nullptr);
            void setImage(const image::Image &img);
            void setImage(const image::Image &img,const std::vector<std::vector<bool>> &mask);
            void setSpectrum(const image::Image &img);
            void setSpectrum(image::Image &&img);
            void setMask(const std::vector<std::vector<bool>> &mask,bool invert=false);
            image::Image& getSpectrum() const;
            [[nodiscard]] image::Real getTotalEnergy() const;
            [[nodiscard]] image::Real getRemainingEnergy() const;

        };

    } // spectrum

#endif //IMAGEPROCESSING_SPECTRUMFILTERVIEW_H
