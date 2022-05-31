//
// Created by ramizouari on 01/05/22.
//

#ifndef IMAGEPROCESSING_MAINWINDOW_H
#define IMAGEPROCESSING_MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QLabel>
#include <QScrollArea>
#include "image/Image.h"
#include "gui/statusbar/ImageInformationBar.h"
#include "imageview.h"
#include "image/ImageWriter.h"

namespace GUI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;
        void saveToFile(QString path);
        void updateSelectedFile(QString path);

    private:
       // Ui::MainWindow *ui;
        QMenu *fileMenu,*statsMenu,*editMenu,*aboutMenu,*viewMenu;
       ImageView *imageLabel,*bakImageLabel;
       ImageInformationBar* imageInformationBar;

    public slots:
       void showHistogram();
       void showHistogramCurve();
       void showSpectrum();
       void openImage();
       void saveImage();
       void saveImageAs();
       void addGaussianNoise();
       void addSaltAndPepperNoise();
       void addSpeckleNoise();
       void addSobelFilter();
       void addGaussianBlurFilter();
       void addMedianFilter();
       void addMeanBlurFilter();
       void addBilateralFilter();
       void addLaplacianFilter();
       void addRobertsFilter();
       void about();
       void histogramEqualization();
       void mapContrast();
       void mapContrastSpline();
       void addCustomConvolutionFilter();
       void otsuSegmentation();
       void grayFilter();
       void addSpectralMask();
       void addSpectralFilter();
       void addErosion();
       void addDilation();
       void addOpening();
       void addClosing();
    };
} // GUI

#endif //IMAGEPROCESSING_MAINWINDOW_H
