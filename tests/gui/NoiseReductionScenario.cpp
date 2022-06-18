//
// Created by ramizouari on 06/06/22.
//
//#define TEST_MODE
#include "NoiseReductionScenario.h"
#include "TestUtilities.h"
#include "gui/mainwindow.h"
#include <chrono>
#include <QInputDialog>

using namespace test;
constexpr double probability=0.05;
using namespace std::chrono_literals;



void NoiseReductionScenario::completeTest()
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


/*
 * Save image
 * */
    QAction *saveAsAction= Test::findAction(window.fileMenu,"Save as");
    auto potentialSaveAsActionMissing=Test::actionNotFound("Save as").toStdString();
    //Verify the existence of the action open
    QVERIFY2(saveAsAction, potentialSaveAsActionMissing.c_str());
    Test::FileDialog saveDialog(&window,"Test Save",directory.path());
    //Override save image dialog
    saveAsAction->disconnect();
    QString saveFile;
    connect(saveAsAction,&QAction::triggered,[&saveDialog,&directory=this->directory,&window,&saveFile]
    {
        saveDialog.setOptions(QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);
        saveDialog.selectFile("marbles-edit.ppm");
        //saveDialog.setLabelText(QFileDialog::FileName, "marbles-edit.ppm");
        QTimer::singleShot(5000ms, &saveDialog, [&saveDialog]
        {
            QTest::keyClick(&saveDialog,Qt::Key::Key_Enter);
        });
        saveFile=window.saveImageAsPrivate(&saveDialog);
        /*
         * Copy image to target location
         * */
        QFile::copy(directory.filePath(saveFile),"img/P6/marbles-edit.ppm");
        qApp->processEvents();
    });
    saveAsAction->trigger();

    /*
     * Verify whether the image is saved or not
     * */
    QVERIFY2(QFile(saveFile).exists(),"File Not generated");
    QVERIFY2(QFile(saveFile).size()>0,"File is empty");

   /*
    * Noise is not deterministic, so no need to compare the image
    *
    * QCryptographicHash hash(QCryptographicHash::Algorithm::Sha256);
        QFile file(saveFile);
        file.open(QIODevice::ReadOnly);
        hash.addData(file.readAll());
        file.close();
        QFile checkshum=directory.filePath("marbles.sha");
        checkshum.open(QIODevice::ReadOnly);
        QVERIFY2(hash.result().toHex().toStdString()==checkshum.readAll().toStdString(),"File corrupted");
    */
}

void NoiseReductionScenario::init() {
    directory=QDir::current();
    bool result=directory.cd("img");
    if(!result)
        QFAIL("Folder img does not exist");
    result=directory.cd("P6");
    if(!result)
        QFAIL("Folder img/P6 does not exist");

    QFile::remove(directory.filePath("marbles-edit.ppm"));
    QFile file(directory.filePath("marbles-edit.ppm"));
    file.open(QIODevice::WriteOnly);
    file.close();
}

void NoiseReductionScenario::cleanup()
{
    //QFile::remove(directory.filePath("marbles-edit.ppm"));
}

