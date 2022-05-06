//
// Created by ramizouari on 01/05/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_histogram.h" resolved

#include "Histogram.h"
#include "image/stats.h"
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QToolTip>

namespace GUI {


    Histogram::~Histogram() = default;

    Histogram::Histogram(const std::vector<Real>&H,int binSize, QWidget *parent): Histogram(image::tensor<2>{H},binSize,parent) {}

    Histogram::Histogram(const std::vector<std::vector<Real>>&Hs,int binSize, QWidget *parent): QChartView(new QChart,parent),binSize(binSize) {
        static std::array<std::string,3> titles = {"Red","Green","Blue"};
        static std::array<QColor,3> colors = {QColor(255,0,0),QColor(0,255,0),QColor(0,0,255)};
        constexpr int groupsLimit=16;
        series= new QBarSeries(this);
        chart = this->QChartView::chart();

        QStringList categories;
        int r=0;
        int nbins=Hs.front().size();
        for(const auto &H:Hs) {
            auto set = new QBarSet(Hs.size()==1?"Gray scale":titles[r].c_str());
            for (int i = 0; i < nbins; i += binSize) {
                if (nbins / binSize <= groupsLimit)
                    categories << QString::number(i);
                auto binTotal = std::reduce(H.begin() + i, H.begin() + i + binSize, .0L);
                *set << binTotal;
            }
            series->append(set);
            if(Hs.size()==1)
                continue;
            set->setColor(colors[r]);
            connect(set, &QBarSet::hovered, this,[this,set](bool status,int index)
            {
                for(auto &s:series->barSets()) {
                    auto color=s->color();
                    color.setAlpha(status && s!=set?32:255);
                    s->setColor(color);
                }
            });
            r++;
        }
        series->setBarWidth(Hs.size()==1?.8:1.5);
        chart->addSeries(series);
        chart->setTitle("Histogram of the Image");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        if(nbins/binSize<=groupsLimit) {
            auto axisX = new QBarCategoryAxis;
            axisX->append(categories);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);
        }
        auto axisY=new QValueAxis;
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        this->setRenderHint(QPainter::Antialiasing);

    }

    Histogram::Histogram(const image::Image& image,int binSize, QWidget *parent) : Histogram(image::stats::histogram(image),binSize,parent) {}
} // GUI
