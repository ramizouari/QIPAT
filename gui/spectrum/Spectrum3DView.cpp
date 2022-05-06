//
// Created by ramizouari on 06/05/22.
//

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QPushButton>
#include <QPainter>
#include "Spectrum3DView.h"
#include "image/utils.h"
#include <QLabel>

namespace GUI::spectrum
{
    Spectrum3DView::Spectrum3DView(const image::Image &img, QWidget *parent)
        : QWidget(parent)
    {


    }



    const int sampleCountX = 50;
    const int sampleCountZ = 50;
    const int heightMapGridStepX = 6;
    const int heightMapGridStepZ = 6;
    const float sampleMin = 0.0f;
    const float sampleMax = 100;

    SurfaceGraph::SurfaceGraph(Q3DSurface *surface)
            : m_graph(surface)
    {
        m_graph->setAxisX(new QValue3DAxis);
        m_graph->setAxisY(new QValue3DAxis);
        m_graph->setAxisZ(new QValue3DAxis);

        //! [0]
        m_sqrtSinProxy = new QSurfaceDataProxy();
        m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);
        //! [0]
        fillSqrtSinProxy();

        //! [2]
        QImage heightMapImage(":/maps/mountain");
        m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
        m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
        m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));
        m_heightMapProxy->setValueRanges(34.0f, 40.0f, 18.0f, 24.0f);
        //! [2]
        m_heightMapWidth = heightMapImage.width();
        m_heightMapHeight = heightMapImage.height();
    }

    SurfaceGraph::~SurfaceGraph()
    {
        delete m_graph;
    }

//! [1]
    void SurfaceGraph::fillSqrtSinProxy()
    {
        float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

        QSurfaceDataArray *dataArray = new QSurfaceDataArray;
        dataArray->reserve(sampleCountZ);
        for (int i = 0 ; i < sampleCountZ ; i++) {
            QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
            // Keep values within range bounds, since just adding step can cause minor drift due
            // to the rounding errors.
            float z = qMin(sampleMax, (i * stepZ + sampleMin));
            int index = 0;
            for (int j = 0; j < sampleCountX; j++) {
                float x = qMin(sampleMax, (j * stepX + sampleMin));
                float R = qSqrt(z * z + x * x);
                float y = (qSin(R)  ) ;
                (*newRow)[index++].setPosition(QVector3D(x, y, z));
            }
            *dataArray << newRow;
        }

        m_sqrtSinProxy->resetArray(dataArray);
    }
//! [1]

    void SurfaceGraph::enableSqrtSinModel(bool enable)
    {
        if (enable) {
            //! [3]
            m_sqrtSinSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
            m_sqrtSinSeries->setFlatShadingEnabled(true);

            m_graph->axisX()->setLabelFormat("%.2f");
            m_graph->axisZ()->setLabelFormat("%.2f");
            m_graph->axisX()->setRange(sampleMin, sampleMax);
            m_graph->axisY()->setRange(0.0f, 2.0f);
            m_graph->axisZ()->setRange(sampleMin, sampleMax);
            m_graph->axisX()->setLabelAutoRotation(30);
            m_graph->axisY()->setLabelAutoRotation(90);
            m_graph->axisZ()->setLabelAutoRotation(30);

            m_graph->removeSeries(m_heightMapSeries);
            m_graph->addSeries(m_sqrtSinSeries);
            //! [3]

            //! [8]
            // Reset range sliders for Sqrt&Sin
            m_rangeMinX = sampleMin;
            m_rangeMinZ = sampleMin;
            m_stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
            m_stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
            m_axisMinSliderX->setMaximum(sampleCountX - 2);
            m_axisMinSliderX->setValue(0);
            m_axisMaxSliderX->setMaximum(sampleCountX - 1);
            m_axisMaxSliderX->setValue(sampleCountX - 1);
            m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
            m_axisMinSliderZ->setValue(0);
            m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
            m_axisMaxSliderZ->setValue(sampleCountZ - 1);
            //! [8]
        }
    }

    void SurfaceGraph::enableHeightMapModel(bool enable)
    {
        if (enable) {
            //! [4]
            m_heightMapSeries->setDrawMode(QSurface3DSeries::DrawSurface);
            m_heightMapSeries->setFlatShadingEnabled(false);

            m_graph->axisX()->setLabelFormat("%.1f N");
            m_graph->axisZ()->setLabelFormat("%.1f E");
            m_graph->axisX()->setRange(34.0f, 40.0f);
            m_graph->axisY()->setAutoAdjustRange(true);
            m_graph->axisZ()->setRange(18.0f, 24.0f);

            m_graph->axisX()->setTitle(QStringLiteral("Latitude"));
            m_graph->axisY()->setTitle(QStringLiteral("Height"));
            m_graph->axisZ()->setTitle(QStringLiteral("Longitude"));

            m_graph->removeSeries(m_sqrtSinSeries);
            m_graph->addSeries(m_heightMapSeries);
            //! [4]

            // Reset range sliders for height map
            int mapGridCountX = m_heightMapWidth / heightMapGridStepX;
            int mapGridCountZ = m_heightMapHeight / heightMapGridStepZ;
            m_rangeMinX = 34.0f;
            m_rangeMinZ = 18.0f;
            m_stepX = 6.0f / float(mapGridCountX - 1);
            m_stepZ = 6.0f / float(mapGridCountZ - 1);
            m_axisMinSliderX->setMaximum(mapGridCountX - 2);
            m_axisMinSliderX->setValue(0);
            m_axisMaxSliderX->setMaximum(mapGridCountX - 1);
            m_axisMaxSliderX->setValue(mapGridCountX - 1);
            m_axisMinSliderZ->setMaximum(mapGridCountZ - 2);
            m_axisMinSliderZ->setValue(0);
            m_axisMaxSliderZ->setMaximum(mapGridCountZ - 1);
            m_axisMaxSliderZ->setValue(mapGridCountZ - 1);
        }
    }

    void SurfaceGraph::adjustXMin(int min)
    {
        float minX = m_stepX * float(min) + m_rangeMinX;

        int max = m_axisMaxSliderX->value();
        if (min >= max) {
            max = min + 1;
            m_axisMaxSliderX->setValue(max);
        }
        float maxX = m_stepX * max + m_rangeMinX;

        setAxisXRange(minX, maxX);
    }

    void SurfaceGraph::adjustXMax(int max)
    {
        float maxX = m_stepX * float(max) + m_rangeMinX;

        int min = m_axisMinSliderX->value();
        if (max <= min) {
            min = max - 1;
            m_axisMinSliderX->setValue(min);
        }
        float minX = m_stepX * min + m_rangeMinX;

        setAxisXRange(minX, maxX);
    }

    void SurfaceGraph::adjustZMin(int min)
    {
        float minZ = m_stepZ * float(min) + m_rangeMinZ;

        int max = m_axisMaxSliderZ->value();
        if (min >= max) {
            max = min + 1;
            m_axisMaxSliderZ->setValue(max);
        }
        float maxZ = m_stepZ * max + m_rangeMinZ;

        setAxisZRange(minZ, maxZ);
    }

    void SurfaceGraph::adjustZMax(int max)
    {
        float maxX = m_stepZ * float(max) + m_rangeMinZ;

        int min = m_axisMinSliderZ->value();
        if (max <= min) {
            min = max - 1;
            m_axisMinSliderZ->setValue(min);
        }
        float minX = m_stepZ * min + m_rangeMinZ;

        setAxisZRange(minX, maxX);
    }

//! [5]
    void SurfaceGraph::setAxisXRange(float min, float max)
    {
        m_graph->axisX()->setRange(min, max);
    }

    void SurfaceGraph::setAxisZRange(float min, float max)
    {
        m_graph->axisZ()->setRange(min, max);
    }
//! [5]

//! [6]
    void SurfaceGraph::changeTheme(int theme)
    {
        m_graph->activeTheme()->setType(Q3DTheme::Theme(theme));
    }
//! [6]

    void SurfaceGraph::setBlackToYellowGradient()
    {
        //! [7]
        QLinearGradient gr;
        gr.setColorAt(0.0, Qt::black);
        gr.setColorAt(0.33, Qt::blue);
        gr.setColorAt(0.67, Qt::red);
        gr.setColorAt(1.0, Qt::yellow);

        m_graph->seriesList().at(0)->setBaseGradient(gr);
        m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
        //! [7]
    }

    void SurfaceGraph::setGreenToRedGradient()
    {
        QLinearGradient gr;
        gr.setColorAt(0.0, Qt::darkGreen);
        gr.setColorAt(0.5, Qt::yellow);
        gr.setColorAt(0.8, Qt::red);
        gr.setColorAt(1.0, Qt::darkRed);

        m_graph->seriesList().at(0)->setBaseGradient(gr);
        m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    }

    SurfaceGraph::SurfaceGraph(Q3DSurface *surface,const image::Image &img)   : m_graph(surface)
    {
        m_graph->setAxisX(new QValue3DAxis);
        m_graph->setAxisY(new QValue3DAxis);
        m_graph->setAxisZ(new QValue3DAxis);

        //! [0]
        m_sqrtSinProxy = new QSurfaceDataProxy();
        m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);
        //! [0]
        fillImageProxy(img);

        //! [2]
        QImage heightMapImage(":/maps/mountain");
        m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
        m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
        m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));
        m_heightMapProxy->setValueRanges(34.0f, 40.0f, 18.0f, 24.0f);
        //! [2]
        m_heightMapWidth = heightMapImage.width();
        m_heightMapHeight = heightMapImage.height();
    }


    void SurfaceGraph::fillImageProxy(const image::Image&image)
    {
        int stepX = 1,stepZ = 1;

        QSurfaceDataArray *dataArray = new QSurfaceDataArray;
        dataArray->reserve(image.width);
        for (int i = 0 ; i < image.width ; i++) {
            QSurfaceDataRow *newRow = new QSurfaceDataRow(image.height);
            // Keep values within range bounds, since just adding step can cause minor drift due
            // to the rounding errors.
            int index = 0;
            for (int j = 0; j < image.height; j++)
            {
                (*newRow)[index++].setPosition(QVector3D(i, image(i,j), j));
            }
            *dataArray << newRow;
        }

        m_sqrtSinProxy->resetArray(dataArray);

    }

    QWidget *test::createGraph(QWidget *parent) {
        Q3DSurface *graph = new Q3DSurface();
        QWidget *container = QWidget::createWindowContainer(graph, parent, Qt::Dialog);
        //! [0]

        if (!graph->hasContext()) {
            QMessageBox msgBox;
            msgBox.setText("Couldn't initialize the OpenGL context.");
            msgBox.exec();
            return nullptr;
        }

        QSize screenSize = graph->screen()->size();
        container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
        container->setMaximumSize(screenSize);
        container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        container->setFocusPolicy(Qt::StrongFocus);

        //! [1]
        QWidget *widget = new QWidget;
        QHBoxLayout *hLayout = new QHBoxLayout(widget);
        QVBoxLayout *vLayout = new QVBoxLayout();
        hLayout->addWidget(container, 1);
        hLayout->addLayout(vLayout);
        vLayout->setAlignment(Qt::AlignTop);
        //! [1]

        widget->setWindowTitle(QStringLiteral("Surface example"));

        QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

        QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
        sqrtSinModelRB->setText(QStringLiteral("Sqrt && Sin"));
        sqrtSinModelRB->setChecked(false);

        QRadioButton *heightMapModelRB = new QRadioButton(widget);
        heightMapModelRB->setText(QStringLiteral("Height Map"));
        heightMapModelRB->setChecked(false);

        QVBoxLayout *modelVBox = new QVBoxLayout;
        modelVBox->addWidget(sqrtSinModelRB);
        modelVBox->addWidget(heightMapModelRB);
        modelGroupBox->setLayout(modelVBox);

        QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

        QRadioButton *modeNoneRB = new QRadioButton(widget);
        modeNoneRB->setText(QStringLiteral("No selection"));
        modeNoneRB->setChecked(false);

        QRadioButton *modeItemRB = new QRadioButton(widget);
        modeItemRB->setText(QStringLiteral("Item"));
        modeItemRB->setChecked(false);

        QRadioButton *modeSliceRowRB = new QRadioButton(widget);
        modeSliceRowRB->setText(QStringLiteral("Row Slice"));
        modeSliceRowRB->setChecked(false);

        QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
        modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
        modeSliceColumnRB->setChecked(false);

        QVBoxLayout *selectionVBox = new QVBoxLayout;
        selectionVBox->addWidget(modeNoneRB);
        selectionVBox->addWidget(modeItemRB);
        selectionVBox->addWidget(modeSliceRowRB);
        selectionVBox->addWidget(modeSliceColumnRB);
        selectionGroupBox->setLayout(selectionVBox);

        QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
        axisMinSliderX->setMinimum(0);
        axisMinSliderX->setTickInterval(1);
        axisMinSliderX->setEnabled(true);
        QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
        axisMaxSliderX->setMinimum(1);
        axisMaxSliderX->setTickInterval(1);
        axisMaxSliderX->setEnabled(true);
        QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
        axisMinSliderZ->setMinimum(0);
        axisMinSliderZ->setTickInterval(1);
        axisMinSliderZ->setEnabled(true);
        QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
        axisMaxSliderZ->setMinimum(1);
        axisMaxSliderZ->setTickInterval(1);
        axisMaxSliderZ->setEnabled(true);

        QComboBox *themeList = new QComboBox(widget);
        themeList->addItem(QStringLiteral("Qt"));
        themeList->addItem(QStringLiteral("Primary Colors"));
        themeList->addItem(QStringLiteral("Digia"));
        themeList->addItem(QStringLiteral("Stone Moss"));
        themeList->addItem(QStringLiteral("Army Blue"));
        themeList->addItem(QStringLiteral("Retro"));
        themeList->addItem(QStringLiteral("Ebony"));
        themeList->addItem(QStringLiteral("Isabelle"));

        QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

        QLinearGradient grBtoY(0, 0, 1, 100);
        grBtoY.setColorAt(1.0, Qt::black);
        grBtoY.setColorAt(0.67, Qt::blue);
        grBtoY.setColorAt(0.33, Qt::red);
        grBtoY.setColorAt(0.0, Qt::yellow);
        QPixmap pm(24, 100);
        QPainter pmp(&pm);
        pmp.setBrush(QBrush(grBtoY));
        pmp.setPen(Qt::NoPen);
        pmp.drawRect(0, 0, 24, 100);
        QPushButton *gradientBtoYPB = new QPushButton(widget);
        gradientBtoYPB->setIcon(QIcon(pm));
        gradientBtoYPB->setIconSize(QSize(24, 100));

        QLinearGradient grGtoR(0, 0, 1, 100);
        grGtoR.setColorAt(1.0, Qt::darkGreen);
        grGtoR.setColorAt(0.5, Qt::yellow);
        grGtoR.setColorAt(0.2, Qt::red);
        grGtoR.setColorAt(0.0, Qt::darkRed);
        pmp.setBrush(QBrush(grGtoR));
        pmp.drawRect(0, 0, 24, 100);
        QPushButton *gradientGtoRPB = new QPushButton(widget);
        gradientGtoRPB->setIcon(QIcon(pm));
        gradientGtoRPB->setIconSize(QSize(24, 100));

        QHBoxLayout *colorHBox = new QHBoxLayout;
        colorHBox->addWidget(gradientBtoYPB);
        colorHBox->addWidget(gradientGtoRPB);
        colorGroupBox->setLayout(colorHBox);

        vLayout->addWidget(modelGroupBox);
        vLayout->addWidget(selectionGroupBox);
        vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
        vLayout->addWidget(axisMinSliderX);
        vLayout->addWidget(axisMaxSliderX);
        vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
        vLayout->addWidget(axisMinSliderZ);
        vLayout->addWidget(axisMaxSliderZ);
        vLayout->addWidget(new QLabel(QStringLiteral("Theme")));
        vLayout->addWidget(themeList);
        vLayout->addWidget(colorGroupBox);

        widget->show();

        SurfaceGraph *modifier = new SurfaceGraph(graph);

        QObject::connect(heightMapModelRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::enableHeightMapModel);
        QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::enableSqrtSinModel);
        QObject::connect(modeNoneRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeNone);
        QObject::connect(modeItemRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeItem);
        QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeSliceRow);
        QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeSliceColumn);
        QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustXMin);
        QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustXMax);
        QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustZMin);
        QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustZMax);
        QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
                         modifier, SLOT(changeTheme(int)));
        QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                         modifier, &SurfaceGraph::setBlackToYellowGradient);
        QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                         modifier, &SurfaceGraph::setGreenToRedGradient);

        modifier->setAxisMinSliderX(axisMinSliderX);
        modifier->setAxisMaxSliderX(axisMaxSliderX);
        modifier->setAxisMinSliderZ(axisMinSliderZ);
        modifier->setAxisMaxSliderZ(axisMaxSliderZ);

        sqrtSinModelRB->setChecked(true);
        modeItemRB->setChecked(true);
        themeList->setCurrentIndex(2);
        return widget;
    }


    QWidget *test::createGraph(const image::Image &img,QWidget *parent) {
        Q3DSurface *graph = new Q3DSurface();
        QWidget *container = QWidget::createWindowContainer(graph);
        //! [0]

        if (!graph->hasContext()) {
            QMessageBox msgBox;
            msgBox.setText("Couldn't initialize the OpenGL context.");
            msgBox.exec();
            return nullptr;
        }

        QSize screenSize = graph->screen()->size();
        container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
        container->setMaximumSize(screenSize);
        container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        container->setFocusPolicy(Qt::StrongFocus);

        //! [1]
        QWidget *widget = new QDialog(parent);
        QHBoxLayout *hLayout = new QHBoxLayout(widget);
        QVBoxLayout *vLayout = new QVBoxLayout();
        hLayout->addWidget(container, 1);
        hLayout->addLayout(vLayout);
        vLayout->setAlignment(Qt::AlignTop);
        //! [1]

        widget->setWindowTitle(QStringLiteral("Surface example"));

        QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

        QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
        sqrtSinModelRB->setText(QStringLiteral("Sqrt && Sin"));
        sqrtSinModelRB->setChecked(false);

        QRadioButton *heightMapModelRB = new QRadioButton(widget);
        heightMapModelRB->setText(QStringLiteral("Height Map"));
        heightMapModelRB->setChecked(false);

        QVBoxLayout *modelVBox = new QVBoxLayout;
        modelVBox->addWidget(sqrtSinModelRB);
        modelVBox->addWidget(heightMapModelRB);
        modelGroupBox->setLayout(modelVBox);

        QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

        QRadioButton *modeNoneRB = new QRadioButton(widget);
        modeNoneRB->setText(QStringLiteral("No selection"));
        modeNoneRB->setChecked(false);

        QRadioButton *modeItemRB = new QRadioButton(widget);
        modeItemRB->setText(QStringLiteral("Item"));
        modeItemRB->setChecked(false);

        QRadioButton *modeSliceRowRB = new QRadioButton(widget);
        modeSliceRowRB->setText(QStringLiteral("Row Slice"));
        modeSliceRowRB->setChecked(false);

        QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
        modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
        modeSliceColumnRB->setChecked(false);

        QVBoxLayout *selectionVBox = new QVBoxLayout;
        selectionVBox->addWidget(modeNoneRB);
        selectionVBox->addWidget(modeItemRB);
        selectionVBox->addWidget(modeSliceRowRB);
        selectionVBox->addWidget(modeSliceColumnRB);
        selectionGroupBox->setLayout(selectionVBox);

        QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
        axisMinSliderX->setMinimum(0);
        axisMinSliderX->setTickInterval(1);
        axisMinSliderX->setEnabled(true);
        QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
        axisMaxSliderX->setMinimum(1);
        axisMaxSliderX->setTickInterval(1);
        axisMaxSliderX->setEnabled(true);
        QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
        axisMinSliderZ->setMinimum(0);
        axisMinSliderZ->setTickInterval(1);
        axisMinSliderZ->setEnabled(true);
        QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
        axisMaxSliderZ->setMinimum(1);
        axisMaxSliderZ->setTickInterval(1);
        axisMaxSliderZ->setEnabled(true);

        QComboBox *themeList = new QComboBox(widget);
        themeList->addItem(QStringLiteral("Qt"));
        themeList->addItem(QStringLiteral("Primary Colors"));
        themeList->addItem(QStringLiteral("Digia"));
        themeList->addItem(QStringLiteral("Stone Moss"));
        themeList->addItem(QStringLiteral("Army Blue"));
        themeList->addItem(QStringLiteral("Retro"));
        themeList->addItem(QStringLiteral("Ebony"));
        themeList->addItem(QStringLiteral("Isabelle"));

        QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

        QLinearGradient grBtoY(0, 0, 1, 100);
        grBtoY.setColorAt(1.0, Qt::black);
        grBtoY.setColorAt(0.67, Qt::blue);
        grBtoY.setColorAt(0.33, Qt::red);
        grBtoY.setColorAt(0.0, Qt::yellow);
        QPixmap pm(24, 100);
        QPainter pmp(&pm);
        pmp.setBrush(QBrush(grBtoY));
        pmp.setPen(Qt::NoPen);
        pmp.drawRect(0, 0, 24, 100);
        QPushButton *gradientBtoYPB = new QPushButton(widget);
        gradientBtoYPB->setIcon(QIcon(pm));
        gradientBtoYPB->setIconSize(QSize(24, 100));

        QLinearGradient grGtoR(0, 0, 1, 100);
        grGtoR.setColorAt(1.0, Qt::darkGreen);
        grGtoR.setColorAt(0.5, Qt::yellow);
        grGtoR.setColorAt(0.2, Qt::red);
        grGtoR.setColorAt(0.0, Qt::darkRed);
        pmp.setBrush(QBrush(grGtoR));
        pmp.drawRect(0, 0, 24, 100);
        QPushButton *gradientGtoRPB = new QPushButton(widget);
        gradientGtoRPB->setIcon(QIcon(pm));
        gradientGtoRPB->setIconSize(QSize(24, 100));

        QHBoxLayout *colorHBox = new QHBoxLayout;
        colorHBox->addWidget(gradientBtoYPB);
        colorHBox->addWidget(gradientGtoRPB);
        colorGroupBox->setLayout(colorHBox);

        vLayout->addWidget(modelGroupBox);
        vLayout->addWidget(selectionGroupBox);
        vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
        vLayout->addWidget(axisMinSliderX);
        vLayout->addWidget(axisMaxSliderX);
        vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
        vLayout->addWidget(axisMinSliderZ);
        vLayout->addWidget(axisMaxSliderZ);
        vLayout->addWidget(new QLabel(QStringLiteral("Theme")));
        vLayout->addWidget(themeList);
        vLayout->addWidget(colorGroupBox);

        widget->show();

        SurfaceGraph *modifier = new SurfaceGraph(graph,img);

        QObject::connect(heightMapModelRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::enableHeightMapModel);
        QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::enableSqrtSinModel);
        QObject::connect(modeNoneRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeNone);
        QObject::connect(modeItemRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeItem);
        QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeSliceRow);
        QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeSliceColumn);
        QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustXMin);
        QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustXMax);
        QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustZMin);
        QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustZMax);
        QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
                         modifier, SLOT(changeTheme(int)));
        QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                         modifier, &SurfaceGraph::setBlackToYellowGradient);
        QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                         modifier, &SurfaceGraph::setGreenToRedGradient);

        modifier->setAxisMinSliderX(axisMinSliderX);
        modifier->setAxisMaxSliderX(axisMaxSliderX);
        modifier->setAxisMinSliderZ(axisMinSliderZ);
        modifier->setAxisMaxSliderZ(axisMaxSliderZ);

        sqrtSinModelRB->setChecked(true);
        modeItemRB->setChecked(true);
        themeList->setCurrentIndex(2);
        return widget;
    }
} // spectrum