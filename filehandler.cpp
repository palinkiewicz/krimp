#include "filehandler.h"
#include <QImage>
#include <stdexcept>
#include <fstream>
#include <iostream>

FileHandler::FileHandler() {}

bool FileHandler::savePpm(std::string path, QImage* qImage) {
    if (qImage->isNull()) {
        std::cerr << "Error: Invalid QImage provided for saving." << std::endl;
        return false;
    }

    QImage imageToSave = qImage->convertToFormat(QImage::Format_RGB888);

    std::ofstream outFile(path, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << path << std::endl;
        return false;
    }

    outFile << "P6\n"
            << imageToSave.width() << " " << imageToSave.height() << "\n255\n";

    for (int y = 0; y < imageToSave.height(); ++y) {
        for (int x = 0; x < imageToSave.width(); ++x) {
            QRgb pixel = imageToSave.pixel(x, y);
            unsigned char rgb[] = {
                static_cast<unsigned char>(qRed(pixel)),
                static_cast<unsigned char>(qGreen(pixel)),
                static_cast<unsigned char>(qBlue(pixel))
            };
            outFile.write(reinterpret_cast<const char*>(rgb), sizeof(rgb));
        }
    }

    outFile.close();
    return true;
}

QImage* FileHandler::loadPpm(std::string path) {
    std::ifstream inFile(path, std::ios::binary);
    if (!inFile.is_open()) {
        throw std::runtime_error("Error: Unable to open file for reading: " + path);
    }

    std::string magicNumber;
    inFile >> magicNumber;
    if (magicNumber != "P6") {
        throw std::runtime_error("Error: Unsupported PPM format or invalid file.");
    }

    int width, height, maxColorValue;
    inFile >> width >> height >> maxColorValue;
    inFile.ignore();

    if (maxColorValue != 255) {
        throw std::runtime_error("Error: Only 8-bit PPM files are supported.");
    }

    QImage* qImage = new QImage(width, height, QImage::Format_RGB888);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char rgb[3];
            inFile.read(reinterpret_cast<char*>(rgb), sizeof(rgb));
            qImage->setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }
    }

    inFile.close();
    return qImage;
}
