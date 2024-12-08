#include "mainwindow.h"
#include "filehandler.h"
#include <iostream>

#include <QImage>
#include <QApplication>

int main(int argc, char *argv[])
{
    QImage qImage(3, 2, QImage::Format_RGB888);
    qImage.setPixel(0, 0, qRgb(255, 0, 0)); // Red
    qImage.setPixel(1, 0, qRgb(0, 255, 0)); // Green
    qImage.setPixel(2, 0, qRgb(0, 0, 255)); // Blue
    qImage.setPixel(0, 1, qRgb(255, 255, 0)); // Yellow
    qImage.setPixel(1, 1, qRgb(255, 255, 255)); // White
    qImage.setPixel(2, 1, qRgb(0, 0, 0)); // Black

    FileHandler fs;
    fs.savePpm("/home/pogro/test.ppm", qImage);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
