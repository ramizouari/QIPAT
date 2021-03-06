//
// Created by ramizouari on 07/06/22.
//
#include <QObject>
#include <QDir>

#ifndef IMAGEPROCESSING_OTSUALGORITHMTEST_H
#define IMAGEPROCESSING_OTSUALGORITHMTEST_H

namespace test
{
    class MaskDetectionScenario : public QObject {
    Q_OBJECT
    private slots:
        void init();
        void completeTest();
        void cleanup();
    private:
        QDir directory;
    };
}


#endif //IMAGEPROCESSING_OTSUALGORITHMTEST_H
