//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_MEANBLURFORM_H
#define IMAGEPROCESSING_MEANBLURFORM_H

#include <QSpinBox>
#include "FilterForm.h"

namespace GUI::spectrum::filter {

    class MeanBlurForm :public FilterForm
    {
    Q_OBJECT
    public:
        explicit MeanBlurForm(int width, int height, QWidget *parent = nullptr);
        ~MeanBlurForm() override = default;
        [[nodiscard]] image::Image apply(const image::Image &src) const override;
    private:
        QFormLayout *mainLayout;
        QSpinBox *inputDimension;
    };

} // filter

#endif //IMAGEPROCESSING_MEANBLURFORM_H
