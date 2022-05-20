//
// Created by ramizouari on 16/05/22.
//

#ifndef IMAGEPROCESSING_FUNCTIONFILTERFORM_H
#define IMAGEPROCESSING_FUNCTIONFILTERFORM_H

#include <QPlainTextEdit>
#include "FilterForm.h"

namespace GUI::spectrum::filter {

    class FunctionFilterForm : public FilterForm {
        Q_OBJECT
    public:
        FunctionFilterForm(int width, int height, QWidget *parent = nullptr);
        ~FunctionFilterForm() override = default;
        [[nodiscard]] image::Image apply(const image::Image &src) const override;
        void setImage(const image::Image &img,image::Real totalEnergy);
        void setImage(const image::Image *imagePtr, image::Real totalEnergy);
    private:
        QPlainTextEdit* expressionInput;
        const image::Image *imagePtr;
        image::Real totalEnergy;
    };

} // filter

#endif //IMAGEPROCESSING_FUNCTIONFILTERFORM_H
