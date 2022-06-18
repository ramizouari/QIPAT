//
// Created by ramizouari on 07/06/22.
//

#include <QTestAccessibility>
#include <QtTestGui>
#include "MaskDetectionScenario.h"
#include "gui/mainwindow.h"
#include "TestUtilities.h"
#include <QTimer>
#include <QSpinBox>
#include <QCheckBox>

using namespace test;
void MaskDetectionScenario::cleanup() {

}

void MaskDetectionScenario::init() {
    directory=QDir::current();
    bool result=directory.cd("img");
    if(!result)
        QFAIL("Folder img does not exist");
    result=directory.cd("P3");
    if(!result)
        QFAIL("Folder img/P3 does not exist");

    QFile::remove(directory.filePath("marbles-edit.ppm"));
    QFile file(directory.filePath("marbles-edit.ppm"));
    file.open(QIODevice::WriteOnly);
    file.close();
}

void MaskDetectionScenario::completeTest()
{
    /*
     * Create main window
     * */
    GUI::MainWindow window(true);
    window.showMaximized();
    QTest::qSleep(1000);
    qApp->processEvents();

    /*
     * Open image
     * */
    QTest::qSleep(3000);
    QAction *openAction= Test::findAction(window.fileMenu,"Open");
    auto potentialOpenActionMissing=Test::actionNotFound("Open").toStdString();
    //Verify the existence of the action open
    QVERIFY2(openAction, potentialOpenActionMissing.c_str());
    //Override open image dialog
    openAction->disconnect();
    Test::FileDialog dialog(&window,"Test Open","");
    using namespace std::chrono_literals;
    connect(openAction,&QAction::triggered,[&dialog,&directory=this->directory,&window]
    {
        dialog.setOptions(QFileDialog::DontUseNativeDialog);
        dialog.setDirectory(directory);
        dialog.selectFile("billCropped.ppm");
        QTimer::singleShot(5000ms, &dialog, [&dialog]{QTest::keyClick(&dialog,Qt::Key::Key_Enter);});
        window.openImagePrivate(&dialog);
        qApp->processEvents();
    });
    QTest::mouseClick(window.editMenu,Qt::MouseButton::LeftButton);
    qApp->processEvents();
    QTest::qSleep(3000);
    //Trigger open image action
    openAction->trigger();
    QTest::qSleep(3000);


    qApp->processEvents();
    QTest::qSleep(3000);

/*
 * Add Laplacian filter to image
 * */
    QAction* laplacianAction= Test::findAction(window.filterMenu, "Laplacian");
    auto potentialLaplacianActionMissing=Test::actionNotFound("Laplacian").toStdString();
    //Verify the existence of the action Laplacian
    QVERIFY2(laplacianAction, potentialLaplacianActionMissing.c_str());
    //override laplacian dialog
    laplacianAction->disconnect();
    GUI::options::FilterDialog laplacianDialog(&window);
    connect(laplacianAction, &QAction::triggered, [&laplacianDialog,&window]
    {
        QTest::qSleep(2000);
        qApp->processEvents();
        QTimer::singleShot(3000ms, &laplacianDialog, [&laplacianDialog]
        {
            auto grayFilter=laplacianDialog.findChildren<GUI::options::GrayFilterInput*>("gray");
            auto thresholdFilter=laplacianDialog.findChildren<QSpinBox*>("threshold");
            for(int i=0;i<5;i++)
            {
                thresholdFilter.first()->setValue(thresholdFilter.first()->value()+1);
                qApp->processEvents();
                QTest::qSleep(200);
            }
            QTest::mouseClick(thresholdFilter.first(),Qt::MouseButton::LeftButton);
            QTest::qSleep(200);
            for(int i=0;i<4;i++)
            {
                QTest::keyClick(grayFilter.first(),Qt::Key::Key_Down);
                qApp->processEvents();
                QTest::qSleep(200);
            }
            QTest::keyClick(grayFilter.first(),Qt::Key::Key_Enter);
            qApp->processEvents();
            QTest::qSleep(2000);
            laplacianDialog.accept();
        });
        window.addLaplacianFilterPrivate(&laplacianDialog);
        qApp->processEvents();
    });
    laplacianAction->trigger();
    QTest::qSleep(1000);


    /*
 * Apply Otsu's segmentation algorithm
 * */
    QAction* otsuAction= Test::findAction(window.editMenu, "Otsu");
    auto potentialOtsuActionMissing=Test::actionNotFound("Otsu").toStdString();
    //Verify the existence of the action Laplacian
    QVERIFY2(otsuAction, potentialOtsuActionMissing.c_str());
    //override laplacian dialog
    otsuAction->disconnect();
    GUI::options::FilterDialog otsuDialog(&window);

    connect(otsuAction, &QAction::triggered, [&otsuDialog,&window]
    {
        QTest::qSleep(2000);
        qApp->processEvents();
        QTimer::singleShot(3000ms, &otsuDialog, [&otsuDialog]
        {
            auto binariseInput=otsuDialog.findChildren<QCheckBox*>("binarise");

            QTest::mouseClick(binariseInput.first(), Qt::MouseButton::LeftButton);
            qApp->processEvents();
            QTest::qSleep(2000);
            otsuDialog.accept();
        });
        window.otsuSegmentationPrivate(&otsuDialog);
        qApp->processEvents();
    });
    otsuAction->trigger();
    QTest::qSleep(2000);

}
