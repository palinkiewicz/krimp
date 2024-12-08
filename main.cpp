#include "mainwindow.h"
#include "image.h"
#include "filesaver.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    FileSaver fs;
    Image img = fs.loadPpm("/home/pogro/test.ppm");

    std::cout << img.getSizeX();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
