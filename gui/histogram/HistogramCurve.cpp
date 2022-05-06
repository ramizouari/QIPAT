//
// Created by ramizouari on 03/05/22.
//

#include "HistogramCurve.h"

namespace GUI::histogram {
        HistogramCurve::HistogramCurve(const std::vector<std::vector<image::Real>> &Hs, bool normalize,
                                       QWidget *parent) : QChartView(parent),normalize(normalize)
       {
           static std::array<QString,3> titles = {tr("Red"),tr("Green"),tr("Blue")};
           static std::array<QColor,3> colors = {QColor(255,0,0),QColor(0,255,0),QColor(0,0,255)};
           auto chart = this->chart();
           if(Hs.size()==3) for(int i=0;i<Hs.size();i++)
           {
                   series.push_back(new QLineSeries(this));
                   auto S=std::reduce(Hs[i].begin(),Hs[i].end());
                   for(int j=0;j<Hs[i].size();j++) {
                       if(!normalize)
                           *series[i] << QPoint(j, Hs[i][j]);
                       else *series[i] << QPointF(j, Hs[i][j]/S);
                   }
                   series[i]->setName(titles[i]);
                   series[i]->setColor(colors[i]);
                   chart->addSeries(series[i]);
           }
           else
           {
               series.push_back(new QLineSeries(this));
               auto &H=Hs.front();
               series.front()->setName(tr("Grey scale"));
               auto S=std::reduce(H.begin(),H.end());
               for(int i=0;i<H.size();i++) {
                   if(!normalize)
                       *series.front() << QPoint(i, H[i]);
                   else *series.front() << QPointF(i, H[i]/S);
               }
               chart->addSeries(series.front());
           }
           chart->setTitle(tr("Histogram Curve of the Image"));
           chart->createDefaultAxes();
           chart->axes(Qt::Orientation::Horizontal).back()->setTitleText(tr("Color Intensity"));
           chart->axes(Qt::Orientation::Vertical).back()->setTitleText(normalize?tr("Probability"):tr("Frequency"));
           chart->setAnimationOptions(QChart::AllAnimations);
           axisX = chart->axes(Qt::Orientation::Horizontal).front();
           axisY = chart->axes(Qt::Orientation::Vertical).front();
           setRenderHint(QPainter::Antialiasing);
       }

    void HistogramCurve::reanimate() {
            for(auto s:series)
                chart()->removeSeries(s);
            for(auto s:series)
                chart()->addSeries(s);
            chart()->createDefaultAxes();
            chart()->axes(Qt::Orientation::Horizontal).back()->setTitleText(tr("Color Intensity"));
            chart()->axes(Qt::Orientation::Vertical).back()->setTitleText(normalize?tr("Probability"):tr("Frequency"));
    }
} // histogram