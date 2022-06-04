//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_HISTOGRAM_H
#define IMAGEPROCESSING_HISTOGRAM_H

#include <QWidget>
#include <QBarSeries>
#include "image/Image.h"
#include <QChartView>

namespace GUI {
//    QT_BEGIN_NAMESPACE
//    namespace Ui { class Histogram; }
//    QT_END_NAMESPACE

    class Histogram : public QChartView {
    Q_OBJECT
    using Real=image::Real;
    public:
        explicit Histogram(const std::vector<Real> &H,int binSize, QWidget *parent = nullptr);
        explicit Histogram(const image::tensor<2> &H,int binSize, QWidget *parent = nullptr);
        explicit Histogram(const image::Image &image,int binSize, QWidget *parent = nullptr);
        ~Histogram() override;

    private:
        //Ui::Histogram *ui;
        int binSize=16;
        QBarSeries *series;
        QChart *chart;
    };
} // GUI

#endif //IMAGEPROCESSING_HISTOGRAM_H
