#include <QApplication>
#include "gui/mainwindow.h"
#include "polynomial/fft.h"
#include "image/utils.h"

int main(int argc, char *argv[]) {
    fft::fast_fourier<>::set_factoriser(image::factorisation::factoriser);
    fft::fast_fourier<false>::set_factoriser(image::factorisation::factoriser);
    fft::fast_ntt<>::set_factoriser(image::factorisation::factoriser);
    fft::fast_ntt<false>::set_factoriser(image::factorisation::factoriser);
    QApplication a(argc, argv);
    GUI::MainWindow window;
    window.showMaximized();
    return QApplication::exec();
}
