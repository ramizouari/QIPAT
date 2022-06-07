//
// Created by ramizouari on 07/06/22.
//
#include <QObject>
#include <QDir>

#define TEST_MODE
#ifndef IMAGEPROCESSING_OTSUALGORITHMTEST_H
#define IMAGEPROCESSING_OTSUALGORITHMTEST_H


class OtsuAlgorithmTest :public QObject {
    Q_OBJECT
private slots:
    void init();
    void completeTest();
    void cleanup();
private:
    QDir directory;
};


#endif //IMAGEPROCESSING_OTSUALGORITHMTEST_H
