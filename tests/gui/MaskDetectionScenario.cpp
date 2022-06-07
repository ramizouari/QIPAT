//
// Created by ramizouari on 07/06/22.
//

#include <QTestAccessibility>
#include <QtTestGui>
#include "OtsuAlgorithmTest.h"
#include "gui/mainwindow.h"
#include "TestUtilities.h"
#include <QTimer>

void OtsuAlgorithmTest::cleanup() {

}

void OtsuAlgorithmTest::init() {
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

void OtsuAlgorithmTest::completeTest()
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
        dialog.selectFile("marbles.ppm");
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
 * Add Noise to image
 * */
    QAction* saltAndPepperAction= Test::findAction(window.noiseMenu,"Salt and Pepper");
    auto potentialSaltPepperActionMissing=Test::actionNotFound("Salt and Pepper").toStdString();
    //Verify the existence of the action Salt and Pepper
    QVERIFY2(saltAndPepperAction, potentialSaltPepperActionMissing.c_str());
    //override salt and pepper dialog
    saltAndPepperAction->disconnect();
    QInputDialog noiseDialog(&window);
    connect(saltAndPepperAction,&QAction::triggered,[&noiseDialog,&window]
    {
        QTest::qSleep(2000);
        noiseDialog.setDoubleValue(probability);
        qApp->processEvents();
        QTimer::singleShot(3000ms, &noiseDialog, [&noiseDialog]{QTest::keyClick(&noiseDialog, Qt::Key::Key_Enter);});
        window.addSaltAndPepperNoisePrivate(&noiseDialog);
        qApp->processEvents();
    });
    saltAndPepperAction->trigger();
    QTest::qSleep(1000);


/*
 * Median Filter to image, to remove salt and pepper noise
 * */
    QAction* medianFilterAction = Test::findAction(window.filterMenu,"Median");
    auto potentialMedianActionMissing=Test::actionNotFound("Median").toStdString();
    //Verify the existence of the action open
    QVERIFY2(medianFilterAction, potentialMedianActionMissing.c_str());
    GUI::options::FilterDialog filterDialog;
    //override median filter dialog
    medianFilterAction->disconnect();
    connect(medianFilterAction,&QAction::triggered,[&filterDialog,&window]
    {
        QTest::qSleep(2000);
        qApp->processEvents();
        QTimer::singleShot(3000ms, &filterDialog, [&filterDialog]{filterDialog.accept(); });
        window.addMedianFilterPrivate(&filterDialog);
        qApp->processEvents();
    });
    medianFilterAction->trigger();
    QTest::qSleep(5000);



}
