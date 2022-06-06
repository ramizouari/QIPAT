//
// Created by ramizouari on 04/06/22.
//

#include <QtTest>
#include <QStyleFactory>

/*
 * This trick is used to force exposing the private members of the class
 * */
#include "ImageViewTest.h"
#include "NoiseReductionScenario.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    int status = 0;
    {
        ImageViewTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    {
        NoiseReductionScenario tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    return status;
}