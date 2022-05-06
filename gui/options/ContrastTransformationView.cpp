//
// Created by ramizouari on 03/05/22.
//

#include <sstream>
#include "ContrastTransformationView.h"

image::Real metric(const image::Vector2 &u,const image::Vector2 &v) {
    auto delta= v-u;
    return std::abs(delta[0])+std::abs(delta[1]);
}


namespace GUI::options {
        ContrastTransformationView::ContrastTransformationView(QWidget *parent) : QChartView(parent) {
            chart = this->QChartView::chart();
            referenceSeries = new QLineSeries(chart);
            series = new QLineSeries(chart);
            *referenceSeries << QPoint(0, 0) << QPoint(255, 255);
            auto referencePen = referenceSeries->pen();
            referencePen.setStyle(Qt::DotLine);
            referencePen.setColor(Qt::GlobalColor::darkMagenta);
            referencePen.setWidth(2);
            referenceSeries->setPen(referencePen);

            *series << QPoint(0, 0) << QPoint(255, 255);
            auto pen = series->pen();
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::GlobalColor::darkGreen);
            pen.setWidth(2);
            series->setPen(pen);

            referenceSeries->setName(tr("Identity"));
            series->setName(tr("Contrast"));
            series->setPointsVisible();
            chart->addSeries(referenceSeries);
            chart->addSeries(series);
            //chart->addSeries(scatterSeries);
            chart->createDefaultAxes();
            setRenderHint(QPainter::Antialiasing);

        }

        void ContrastTransformationView::addOrReplace(int id, int x, int y)
        {
            if(id<series->count())
                series->replace(id, QPoint(x, y));
            else
                series->append(QPoint(x, y));
            std::stringstream stream;
            stream << "Id: " << id << "\tx: " << x << "\ty: " << y << "\tcount: " << series->count();
            qDebug("%s", stream.str().c_str());
            update();
        }

        void ContrastTransformationView::appendPoint() {
            series->insert(series->count()-1,QPoint(128,128));
            //scatterSeries->insert(series->count()-2,QPoint(128,128));
        }

        void ContrastTransformationView::removePoint(int id) {
            qDebug("Id: %d", id);
            series->remove(id);
            //scatterSeries->remove(id-1);
        }

        std::vector<image::Vector2> ContrastTransformationView::getPoints()
        {
            std::vector<image::Vector2> points;
            auto P=series->points();
            std::transform(P.begin(),P.end(),std::back_inserter(points),[](const QPointF& p){return image::Vector2({p.x(),p.y()});});
            return points;
        }

        std::vector<std::pair<image::Real, image::Real>> ContrastTransformationView::getPointsPair()
        {
            std::vector<std::pair<image::Real, image::Real>> points;
            auto P=series->points();
            std::transform(P.begin(),P.end(),std::back_inserter(points),[](const QPointF& p){return std::make_pair(p.x(),p.y());});
            return points;
        }
    } // options