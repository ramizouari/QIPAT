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
#include "imageview.h"
#include "gui/statusbar/ImageInformationBar.h"

namespace GUI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;

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
       void addCustomConvolutionFilter();
       void otsuSegmentation();
       void grayFilter();
       void addSpectralFilter();
    };
} // GUI

#endif //IMAGEPROCESSING_MAINWINDOW_H
