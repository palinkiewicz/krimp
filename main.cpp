#include "mainwindow.h"
#include "filehandler.h"
#include <iostream>

#include <QImage>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
