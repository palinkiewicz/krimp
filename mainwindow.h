#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QPixmap>

class FileHandler;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// private slots:
//     void on_actionOpen_triggered();
//     void on_actionSave_triggered();

private:
    void updateImageDisplay();
    void saveImage();
    void openImage();
    Ui::MainWindow *ui;
    QImage *image;
    QLabel *imageLabel;
    FileHandler *fh;
    double zoomFactor;
};

#endif // MAINWINDOW_H
