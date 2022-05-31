//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_HISTOGRAMCURVE_H
#define IMAGEPROCESSING_HISTOGRAMCURVE_H

#include <QChartView>
#include <QLineSeries>
#include "image/Image.h"

namespace GUI::histogram {

        class HistogramCurve : public QChartView
        {
            Q_OBJECT
        public:
            HistogramCurve(const std::vector<std::vector<image::Real>> &Hs,bool normalize,QWidget *parent = nullptr);
            ~HistogramCurve() override =default;
            void reanimate();
        private:
            std::vector<QLineSeries*> series;
            QAbstractAxis *axisX, *axisY;
            bool normalize;
        };

    } // histogram

#endif //IMAGEPROCESSING_HISTOGRAMCURVE_H
