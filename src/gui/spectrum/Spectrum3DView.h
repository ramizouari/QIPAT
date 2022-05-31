//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUM3DVIEW_H
#define IMAGEPROCESSING_SPECTRUM3DVIEW_H

#include <QWidget>
#include <Q3DSurface>
#include <QHeightMapSurfaceDataProxy>
#include <QSurfaceDataProxy>
#include <QSurface3DSeries>
#include <QSlider>
#include "image/Image.h"

namespace GUI::spectrum {

        class Spectrum3DView : public QWidget {
        public:
            explicit Spectrum3DView(const image::Image &img, QWidget *parent = nullptr);
        };

    class SurfaceGraph : public QObject
    {
    Q_OBJECT
    public:
        explicit SurfaceGraph(Q3DSurface *surface);
        explicit SurfaceGraph(Q3DSurface *surface, const image::Image &img);
        ~SurfaceGraph();

        void enableHeightMapModel(bool enable);
        void enableSqrtSinModel(bool enable);

        //! [0]
        void toggleModeNone() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
        void toggleModeItem() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }
        void toggleModeSliceRow() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                                              | QAbstract3DGraph::SelectionSlice); }
        void toggleModeSliceColumn() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                                                 | QAbstract3DGraph::SelectionSlice); }
        //! [0]

        void setBlackToYellowGradient();
        void setGreenToRedGradient();

        void setAxisMinSliderX(QSlider *slider) { m_axisMinSliderX = slider; }
        void setAxisMaxSliderX(QSlider *slider) { m_axisMaxSliderX = slider; }
        void setAxisMinSliderZ(QSlider *slider) { m_axisMinSliderZ = slider; }
        void setAxisMaxSliderZ(QSlider *slider) { m_axisMaxSliderZ = slider; }

        void adjustXMin(int min);
        void adjustXMax(int max);
        void adjustZMin(int min);
        void adjustZMax(int max);

    public Q_SLOTS:
        void changeTheme(int theme);

    private:
        Q3DSurface *m_graph;
        QHeightMapSurfaceDataProxy *m_heightMapProxy;
        QSurfaceDataProxy *m_sqrtSinProxy;
        QSurface3DSeries *m_heightMapSeries;
        QSurface3DSeries *m_sqrtSinSeries;

        QSlider *m_axisMinSliderX;
        QSlider *m_axisMaxSliderX;
        QSlider *m_axisMinSliderZ;
        QSlider *m_axisMaxSliderZ;
        float m_rangeMinX;
        float m_rangeMinZ;
        float m_stepX;
        float m_stepZ;
        int m_heightMapWidth;
        int m_heightMapHeight;

        void setAxisXRange(float min, float max);
        void setAxisZRange(float min, float max);
        void fillSqrtSinProxy();
        void fillImageProxy(const image::Image &img);
    };


    namespace test
    {
        QWidget* createGraph(QWidget *parent = nullptr);
        QWidget* createGraph(const image::Image&img,QWidget *parent = nullptr);

    }
} // spectrum


#endif //IMAGEPROCESSING_SPECTRUM3DVIEW_H
