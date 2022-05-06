//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_HISTOGRAMCURVEVIEW_H
#define IMAGEPROCESSING_HISTOGRAMCURVEVIEW_H


#include <QChartView>
#include <QBarSeries>
#include <QLineSeries>
#include <QStackedWidget>
#include "image/Image.h"

namespace GUI
{
    class HistogramCurveView: public QWidget  {
    Q_OBJECT
        using Real=image::Real;
    public:
        explicit HistogramCurveView(const std::vector<Real> &H, QWidget *parent = nullptr);
        explicit HistogramCurveView(const std::vector<std::vector<Real>> &Hs, QWidget *parent = nullptr);
        explicit HistogramCurveView(const image::Image &image, QWidget *parent = nullptr);
        ~HistogramCurveView() override;

    private:
        //Ui::Histogram *ui;
        QStackedWidget *stackedWidget;
        QChartView *frequencyChartView,*probabilityChartView;
    };
}


#endif //IMAGEPROCESSING_HISTOGRAMCURVEVIEW_H
