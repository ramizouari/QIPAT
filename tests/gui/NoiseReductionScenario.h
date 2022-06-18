//
// Created by ramizouari on 06/06/22.
//

#ifndef IMAGEPROCESSING_NOISEREDUCTIONSCENARIO_H
#define IMAGEPROCESSING_NOISEREDUCTIONSCENARIO_H
#include <QtTest/QtTest>
#include <QFileDialog>


namespace test
{
    class NoiseReductionScenario :public QObject
    {
    Q_OBJECT
    private slots:
        void init();
        void completeTest();
        void cleanup();
    private:
        QDir directory;
    };
}


#endif //IMAGEPROCESSING_NOISEREDUCTIONSCENARIO_H
