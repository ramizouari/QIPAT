//
// Created by ramizouari on 15/05/22.
//

#include "FilterForm.h"
#include "image/filter/GaussianBlurFilter.h"

namespace GUI::spectrum::filter {
            FilterForm::FilterForm(int width, int height, QWidget *parent): width(width), height(height), QWidget(parent)
            {
            }

} // filter