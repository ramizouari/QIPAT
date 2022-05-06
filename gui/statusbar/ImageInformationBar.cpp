//
// Created by ramizouari on 01/05/22.
//

#include "ImageInformationBar.h"
#include "image/stats.h"

namespace GUI {
    template<typename ...T>
    std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& t) {
        std::stringstream str;
        std::apply([&str](auto&&... args) { ((str << args << ','), ...); }, t);
        os << '(' << str.str().substr(0, str.str().size() - 1) << ')';
        return os;
    }

    QTextStream& operator<<(QTextStream &H,long double w)
    {
        return H << (double)w;
    }

    template<typename ...T>
    QTextStream& operator<<(QTextStream& os, const std::tuple<T...>& t)
    {
        QString str;
        QTextStream stream(&str);
        std::apply([&stream](auto&&... args) { ((stream << args << QObject::tr(",")), ...); }, t);
        str.back()=QObject::tr(")").toStdString().front();
        os << QObject::tr("(") << str;
        return os;
    }

    void ImageInformationBar::update(const image::Image &image)
    {
        QString string;
        QTextStream stream(&string);
        if(image.nb_channel == 1) {
            stream << tr("Gray level image. ");
            auto [min,max,mean,median,std]=::image::stats::calculateStatistics(image).front();
            stream << tr("x=") << image.width << tr(", y=") << image.height << tr(", ") ;
            stream << tr("min=") << min << tr(", max=") << max << tr(", mean=") << mean << tr(", median=") << median << tr(", std=") << std;
            setText(string);
        }
        else {
            stream << tr("RGB image. ");
            auto [min1,max1,mean1,median1,std1]=::image::stats::calculateStatistics(image)[0];
            auto [min2,max2,mean2,median2,std2]=::image::stats::calculateStatistics(image)[1];
            auto [min3,max3,mean3,median3,std3]=::image::stats::calculateStatistics(image)[2];

            stream << tr("x=") << image.width << ", y=" << image.height << tr(", ") ;
            stream << tr("min=") << std::make_tuple(min1,min2,min3) << tr(", max=") << std::make_tuple(max1,max2,max3)
                << tr(", mean=") << std::make_tuple(mean1,mean2,mean3) << tr(", median=") << std::make_tuple(median1,median2,median3)
                << tr(", std=") << std::make_tuple(std1,std2,std3) ;
            setText(string);
        }


    }

    ImageInformationBar::ImageInformationBar(QWidget *parent) : QLabel(parent) {
        setAlignment(Qt::AlignRight);
    }

} // GUI