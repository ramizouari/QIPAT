//
// Created by ramizouari on 01/05/22.
//

#include "HistogramCurveView.h"
#include "HistogramCurve.h"
#include "image/stats.h"
#include <QLayout>
#include <QRadioButton>
#include <QButtonGroup>

GUI::HistogramCurveView::HistogramCurveView(const std::vector<Real> &H, QWidget *parent): HistogramCurveView(std::vector<std::vector<Real>>{H},parent) {
}

GUI::HistogramCurveView::~HistogramCurveView() = default;

GUI::HistogramCurveView::HistogramCurveView(const image::Image &image, QWidget *parent): HistogramCurveView(image::stats::histogram(image),parent) {
}


GUI::HistogramCurveView::HistogramCurveView(const std::vector<std::vector<Real>> & Hs, QWidget * parent): QWidget(parent)
{
    static std::array<std::string,3> titles = {"Red","Green","Blue"};
    static std::array<QColor,3> colors = {QColor(255,0,0),QColor(0,255,0),QColor(0,0,255)};
    stackedWidget = new QStackedWidget(this);
    probabilityChartView = new histogram::HistogramCurve(Hs,true,stackedWidget);
    frequencyChartView = new histogram::HistogramCurve(Hs,false,stackedWidget);
    stackedWidget->addWidget(frequencyChartView);
    stackedWidget->addWidget(probabilityChartView);
    setLayout(new QVBoxLayout);
    layout()->addWidget(stackedWidget);
    auto holder = new QWidget(this);
    auto group = new QButtonGroup(holder);
    auto frequency = new QRadioButton("Frequency",holder),probability = new QRadioButton("Probability", holder);
    frequency->setChecked(true);
    group->addButton(frequency);
    group->addButton(probability);
    holder->setLayout(new QHBoxLayout);
    holder->layout()->addWidget(frequency);
    holder->layout()->addWidget(probability);
    holder->layout()->setAlignment(Qt::AlignCenter);
    layout()->addWidget(holder);
    connect(group,&QButtonGroup::buttonClicked,[this,probability](QAbstractButton *button)
    {
        stackedWidget->setCurrentIndex(button==probability);
        dynamic_cast<histogram::HistogramCurve*>(stackedWidget->currentWidget())->reanimate();
    });
}
