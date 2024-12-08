#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filehandler.h"
#include "imagemodifier.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateImageDisplay() {
    if (image == nullptr || image->isNull()) {
        return;
    }

    QPixmap pixmap = QPixmap::fromImage(*image).scaled(image->size() * zoomFactor, Qt::KeepAspectRatio, Qt::FastTransformation);
    imageLabel->setPixmap(pixmap);

    resize(pixmap.size());
}

void MainWindow::openImage() {
    std::string filePath = QFileDialog::getOpenFileName(
        this, tr("Open Image"), "", tr("Binary PPM images (*.ppm)")).toStdString();

    if (filePath.empty()) {
        return;
    }

    image = fh->loadPpm(filePath);

    zoomFactor = qMin(
        (double) imageLabel->size().height() / (double) image->size().height(),
        (double) imageLabel->size().width() / (double) image->size().width()
        );

    updateImageDisplay();
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

    statusBar()->showMessage(QString("Zoom: %1%").arg(qRound(zoomFactor * 100)));
}

void MainWindow::zoomOut() {
    zoomFactor /= 1.1;
    updateImageDisplay();

    statusBar()->showMessage(QString("Zoom: %1%").arg(qRound(zoomFactor * 100)));
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
}

// Filters
void MainWindow::filterDesaturate() {
    im->desaturate(image);
    updateImageDisplay();
    statusBar()->showMessage("Image desaturated.");
}

void MainWindow::filterInvertColors() {
    im->invertColors(image);
    updateImageDisplay();
    statusBar()->showMessage("Image's colors inverted.");
}
