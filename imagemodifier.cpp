#include "imagemodifier.h"
#include <QImage>

ImageModifier::ImageModifier() {}

void ImageModifier::desaturate(QImage* image) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            int desaturated = (qRed(pixel) + qGreen(pixel) + qBlue(pixel)) / 3;
            image->setPixel(x, y, qRgb(desaturated, desaturated, desaturated));
        }
    }
}

void ImageModifier::invertColors(QImage* image) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(x, y, qRgb(255 - qRed(pixel), 255 - qGreen(pixel), 255 - qBlue(pixel)));
        }
    }
}
