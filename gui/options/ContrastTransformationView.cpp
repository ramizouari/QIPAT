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

    ContrastSplineTransformationView::ContrastSplineTransformationView(QWidget *parent) : QChartView(parent) {
        chart = this->QChartView::chart();
        referenceSeries = new QLineSeries(chart);
        series = new QLineSeries(chart);
        *referenceSeries << QPoint(0, 0) << QPoint(255, 255);
        auto referencePen = referenceSeries->pen();
        referencePen.setStyle(Qt::DotLine);
        referencePen.setColor(Qt::GlobalColor::darkMagenta);
        //referencePen.setWidth(2);
        referenceSeries->setPen(referencePen);


        values.emplace_back(image::Vector3({0.L,0.L, 1.L}));
        values.emplace_back(image::Vector3({255.L,255.L, 1.L}));
        for(int i=0;i<256;++i)
            *series << QPoint(i,i);

        auto pen = series->pen();
        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::GlobalColor::darkGreen);
        //pen.setWidth(2);
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

    std::vector<image::Vector2> ContrastSplineTransformationView::getAllPoints() {
        std::vector<image::Vector2> points;
        auto P=series->points();
        std::transform(P.begin(),P.end(),std::back_inserter(points),[](const QPointF& p){return image::Vector2({p.x(),p.y()});});
        return points;
    }

    std::vector<std::tuple<image::Real, image::Real, image::Real>>
    ContrastSplineTransformationView::getPointsTriplet() {
        return std::vector<std::tuple<image::Real, image::Real, image::Real>>();
    }

    void ContrastSplineTransformationView::addOrReplace(int id,int x, int y,image::Real dy)
    {
        if(id<values.size())
            values[id]=image::Vector3({(image::Real)x,(image::Real)y,dy});
        else
        {
            auto top=values.back();
            values.pop_back();
            values.emplace_back(image::Vector3({(image::Real) x, (image::Real) y, dy}));
            values.push_back(top);
        }

        if(id > 0)
            updatePointsLeft(id);
        if(id < values.size()-1)
            updatePointsLeft(id+1);

        std::stringstream stream;
        stream << "x: " << x << "\ty: " << y;
        qDebug("%s", stream.str().c_str());
        update();
    }

    void ContrastSplineTransformationView::appendPoint() {
            auto top=values.back();
            values.pop_back();
            values.push_back(image::Vector3({128,128,128}));
            values.push_back(top);
    }

    void ContrastSplineTransformationView::removePoint(int id)
    {
        int n=values.size();
        values.erase(values.begin()+id);
        std::pair L {id-1,values[id-1]},R {id,values[id]};
        image::Vector2 p1({static_cast<image::Real>(L.first),L.second[1]}),
                p2({static_cast<image::Real>(R.first),R.second[1]}),
                t1({p1[0],L.second[2]}),
                t2({p2[0],R.second[2]});
        for(int k=L.second[0];k<R.second[0];++k)
        {
            image::Real t=(static_cast<image::Real>(k)-p1[0])/(p2[0]-p1[0]);
            image::Vector2 p = h00(t)*p1+h10(t)*t1+h01(t)*p2+h11(t)*t2;
            series->replace(k, QPointF(k,p[1]));
        }
    }

    image::Real ContrastSplineTransformationView::h00(image::Real t) {
        return 2*std::pow(t,3)-3*std::pow(t,2)+1;
    }
    image::Real ContrastSplineTransformationView::h10(image::Real t) {
        return std::pow(t,3)-2*std::pow(t,2)+t;
    }
    image::Real ContrastSplineTransformationView::h01(image::Real t) {
        return -2*std::pow(t,3)+3*std::pow(t,2);
    }
    image::Real ContrastSplineTransformationView::h11(image::Real t) {
        return std::pow(t,3)-std::pow(t,2);
    }

    void ContrastSplineTransformationView::updatePointsLeft(int id)
    {
        std::pair L {id-1,values[id-1]},X {id,values[id]};
        image::Vector2 p1({L.second[0],L.second[1]}),
                p2({(X.second[0]),X.second[1]}),
                t1({p1[0],L.second[2]}),
                t2({p2[0],X.second[2]});
        auto dx=X.second[0]-L.second[0];
        for(int k=L.second[0];k<=X.second[0];++k)
        {
            image::Real t=(static_cast<image::Real>(k)-p1[0])/(p2[0]-p1[0]);
            image::Vector2 p = h00(t)*p1+h10(t)*dx*t1+h01(t)*p2+h11(t)*dx*t2;
            series->replace(k, QPointF(k,p[1]));
        }
    }
} // options