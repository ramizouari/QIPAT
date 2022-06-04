//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_FILTERFORM_H
#define IMAGEPROCESSING_FILTERFORM_H
#include <QWidget>
#include <QComboBox>
#include <QFormLayout>
#include "image/filter/Filter.h"
namespace GUI::spectrum::filter {
    class FilterForm : public QWidget{
        Q_OBJECT
    public:
        FilterForm(int width, int height, QWidget *parent = nullptr);
        ~FilterForm() override = default;
        virtual image::Image apply(const image::Image &src) const = 0;

    protected:
        int width, height;
    };
} // filter

#endif //IMAGEPROCESSING_FILTERFORM_H
