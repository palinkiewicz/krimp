#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filehandler.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Add QLabel for displaying the image
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter); // Center-align the image
    //imageLabel->setScaledContents(true);      // Ensure the image scales

    if (!ui->centralwidget->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
        ui->centralwidget->setLayout(layout);  // Set the layout for centralwidget
    }

    // Set QLabel as the central widget
    ui->centralwidget->layout()->addWidget(imageLabel);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openImage);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveImage);
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
}

void MainWindow::openImage() {
    // Open a file dialog to select an image
    std::string filePath = QFileDialog::getOpenFileName(
        this, tr("Open Image"), "", tr("Binary PPM images (*.ppm)")).toStdString();

    if (filePath.empty()) {
        return; // No file selected
    }

    // Load the image
    image = fh->loadPpm(filePath);

    zoomFactor = qMin(
        (double) imageLabel->size().height() / (double) image->size().height(),
        (double) imageLabel->size().width() / (double) image->size().width()
        );

    updateImageDisplay();
}

void MainWindow::saveImage() {
    // Open a file dialog to select the location and name for saving the image
    std::string filePath = QFileDialog::getSaveFileName(
        this, tr("Save Image"), "", tr("Image Files (*.ppm);;All Files (*)")).toStdString();

    // Check if the user canceled the save dialog
    if (filePath.empty()) {
        return; // User canceled the save operation
    }

    if (image->isNull()) {
        // If the pixmap is null, show an error message
        QMessageBox::warning(this, tr("Error"), tr("No image to save!"));
        return;
    }

    // Save the image to the specified file path
    if (!fh->savePpm(filePath, image)) {
        // Show an error if saving fails
        QMessageBox::warning(this, tr("Error"), tr("Failed to save the image."));
    }
}

