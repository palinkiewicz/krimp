#include "filesaver.h"
#include "image.h"
#include "rgbcolor.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

FileSaver::FileSaver() {}

bool FileSaver::savePpm(std::string path, Image img) {
    std::ofstream outFile(path, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << path << std::endl;
        return false;
    }

    outFile << "P6\n"
            << img.getSizeX() << " " << img.getSizeY() << "\n255\n";

    for (unsigned short y = 0; y < img.getSizeY(); ++y) {
        for (unsigned short x = 0; x < img.getSizeX(); ++x) {
            RGBColor pixel = img.pixels[x][y];
            outFile.put(pixel.getR());
            outFile.put(pixel.getG());
            outFile.put(pixel.getB());
        }
    }

    outFile.close();
    return true;
}

Image FileSaver::loadPpm(std::string path) {
    std::ifstream inFile(path, std::ios::binary);
    if (!inFile.is_open()) {
        throw std::runtime_error("Error: Unable to open file for reading: " + path);
    }

    std::string magicNumber;
    inFile >> magicNumber;
    if (magicNumber != "P6") {
        throw std::runtime_error("Error: Unsupported PPM format or invalid file.");
    }

    unsigned short sizeX, sizeY;
    int maxColorValue;
    inFile >> sizeX >> sizeY >> maxColorValue;
    inFile.ignore();

    if (maxColorValue != 255) {
        throw std::runtime_error("Error: Only 8-bit PPM files are supported.");
    }

    RGBColor** pixels = new RGBColor*[sizeX];
    for (unsigned short x = 0; x < sizeX; ++x) {
        pixels[x] = new RGBColor[sizeY];
    }

    for (unsigned short y = 0; y < sizeY; ++y) {
        for (unsigned short x = 0; x < sizeX; ++x) {
            unsigned char r, g, b;
            r = inFile.get();
            g = inFile.get();
            b = inFile.get();
            pixels[x][y] = RGBColor(r, g, b);
        }
    }

    inFile.close();
    return Image(sizeX, sizeY, pixels);
}
