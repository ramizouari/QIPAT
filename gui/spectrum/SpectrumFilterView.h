//
// Created by ramizouari on 14/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMFILTERVIEW_H
#define IMAGEPROCESSING_SPECTRUMFILTERVIEW_H

#include "SpectrumView.h"

namespace GUI::spectrum {

        class SpectrumFilterView:public ImageView {
            std::unique_ptr<image::Image> originalImage;
            std::vector<std::vector<bool>> mask;
            image::Real totalEnergy,remainingEnergy;
        public:
            explicit SpectrumFilterView(const image::Image & img, QWidget *parent = nullptr);
            void setImage(const image::Image &img);
            void setImage(const image::Image &img,const std::vector<std::vector<bool>> &mask);
            void setMask(const std::vector<std::vector<bool>> &mask,bool invert=false);
            [[nodiscard]] image::Real getTotalEnergy() const;
            [[nodiscard]] image::Real getRemainingEnergy() const;
            [[nodiscard]] const std::vector<std::vector<bool>> & getMask() const;
        };

    } // spectrum

#endif //IMAGEPROCESSING_SPECTRUMFILTERVIEW_H
