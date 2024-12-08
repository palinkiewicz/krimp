#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filehandler.h"
#include "imagemodifier.h"
#include "contrastdialog.h"
#include "brightnessdialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("KRIMP"));

    image = nullptr;

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    if (!ui->centralwidget->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        ui->centralwidget->setLayout(layout);
    }

    ui->centralwidget->layout()->addWidget(imageLabel);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openImage);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveImage);

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::zoomOut);

    connect(ui->actionDesaturation, &QAction::triggered, this, &MainWindow::filterDesaturate);
    connect(ui->actionColor_Invertion, &QAction::triggered, this, &MainWindow::filterInvertColors);
    connect(ui->actionContrast, &QAction::triggered, this, &MainWindow::openContrastDialog);
    connect(ui->actionBrightness, &QAction::triggered, this, &MainWindow::openBrightnessDialog);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateImageDisplay() {
    if (image == nullptr || image->isNull()) {
        return;
    }

    QSize imageSize = image->size() * zoomFactor;

    QPixmap pixmap = QPixmap::fromImage(*image).scaled(imageSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    imageLabel->setPixmap(pixmap);

    setMinimumSize(imageSize);
    resize(imageSize);
}

void MainWindow::openImage() {
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open Image"), "", tr("Binary PPM images (*.ppm)"));

    if (filePath.isEmpty()) {
        return;
    }

    image = fh->loadPpm(filePath.toStdString());

    zoomFactor = qMin(
        (double) imageLabel->size().height() / (double) image->size().height(),
        (double) imageLabel->size().width() / (double) image->size().width()
        );

    updateImageDisplay();

    setWindowTitle(tr("KRIMP - %1").arg(QFileInfo(filePath).fileName()));
}

void MainWindow::saveImage() {
    std::string filePath = QFileDialog::getSaveFileName(
        this, tr("Save Image"), "", tr("Image Files (*.ppm);;All Files (*)")).toStdString();

    if (filePath.empty()) {
        return;
    }

    if (image->isNull()) {
        QMessageBox::warning(this, tr("Error"), tr("No image to save!"));
        return;
    }

    if (!fh->savePpm(filePath, image)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save the image."));
    }
}

// Zooming
void MainWindow::zoomIn() {
    zoomFactor *= 1.1;
    updateImageDisplay();

    statusBar()->showMessage(tr("Zoom: %1%").arg(qRound(zoomFactor * 100)));
}

void MainWindow::zoomOut() {
    zoomFactor /= 1.1;
    updateImageDisplay();

    statusBar()->showMessage(tr("Zoom: %1%").arg(qRound(zoomFactor * 100)));
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
}

// Dialogs
void MainWindow::openContrastDialog() {
    ContrastDialog *dialog = new ContrastDialog(this);
    connect(dialog, &ContrastDialog::contrastChanged, this, &MainWindow::filterContrast);
    dialog->exec();
}

void MainWindow::openBrightnessDialog() {
    BrightnessDialog *dialog = new BrightnessDialog(this);
    connect(dialog, &BrightnessDialog::brightnessChanged, this, &MainWindow::filterBrightness);
    dialog->exec();
}

// Filters
void MainWindow::filterDesaturate() {
    im->desaturate(image);
    updateImageDisplay();
    statusBar()->showMessage(tr("Image desaturated."));
}

void MainWindow::filterInvertColors() {
    im->invertColors(image);
    updateImageDisplay();
    statusBar()->showMessage(tr("Image's colors inverted."));
}

void MainWindow::filterContrast(int contrast) {
    im->adjustContrast(image, contrast);
    updateImageDisplay();
    statusBar()->showMessage(tr("Image's contrast changed."));
}

void MainWindow::filterBrightness(int brightness) {
    im->adjustBrightness(image, brightness);
    updateImageDisplay();
    statusBar()->showMessage(tr("Image's brightness changed."));
}
