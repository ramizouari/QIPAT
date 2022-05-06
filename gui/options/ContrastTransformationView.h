//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_CONTRASTTRANSFORMATIONVIEW_H
#define IMAGEPROCESSING_CONTRASTTRANSFORMATIONVIEW_H

#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <set>
#include "image/Image.h"

namespace GUI::options {





        class ContrastTransformationView : public QChartView {
        public:
            explicit ContrastTransformationView(QWidget *parent = nullptr);

            std::vector<image::Vector2> getPoints();
            std::vector<std::pair<image::Real,image::Real>> getPointsPair();
        public slots:
            void addOrReplace(int id,int x,int y);
            void appendPoint();
            void removePoint(int id);
        private:
            QChart *chart;
            QLineSeries *referenceSeries,*series;
        };

    } // options

#endif //IMAGEPROCESSING_CONTRASTTRANSFORMATIONVIEW_H
