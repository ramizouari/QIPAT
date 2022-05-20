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


    class ContrastSplineTransformationView : public QChartView {
    public:
        explicit ContrastSplineTransformationView(QWidget *parent = nullptr);

        std::vector<image::Vector2> getAllPoints();
        std::vector<std::tuple<image::Real,image::Real,image::Real>> getPointsTriplet();
    public slots:
        void addOrReplace(int id,int x,int y,image::Real dy);
        void appendPoint();
        void removePoint(int x);
    private:
        QChart *chart;
        QLineSeries *referenceSeries,*series;
        std::vector<image::Vector3> values;
        static image::Real h00(image::Real x);
        static image::Real h10(image::Real x);
        static image::Real h01(image::Real x);
        static image::Real h11(image::Real x);
        void updatePointsLeft(int id);
    };

    } // options

#endif //IMAGEPROCESSING_CONTRASTTRANSFORMATIONVIEW_H
