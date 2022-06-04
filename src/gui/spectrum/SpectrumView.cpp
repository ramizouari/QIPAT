//
// Created by ramizouari on 06/05/22.
//

#include "SpectrumView.h"
#include "image/utils.h"

namespace GUI::spectrum
{
        SpectrumView::SpectrumView(const image::Image &img, QWidget *parent): ImageView(parent) {
            setImage(new image::Image(image::convolution::imageLogSpectrum(img)));
        }
} // spectrum