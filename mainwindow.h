#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QPixmap>

class FileHandler;
class ImageModifier;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void wheelEvent(QWheelEvent* event);

private:
    Ui::MainWindow *ui;
    QImage *image;
    QLabel *imageLabel;

    FileHandler *fh;
    void saveImage();
    void openImage();
    void updateImageDisplay();

    double zoomFactor;
    void zoomIn();
    void zoomOut();

    ImageModifier *im;
    void filterDesaturate();
    void filterInvertColors();
};

#endif // MAINWINDOW_H
