#include "imagemodifier.h"
#include <QImage>
#include <QDebug>

ImageModifier::ImageModifier() {}

int ImageModifier::trunc(int value) {
    return qBound(0, value, 255);
}

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

    unsigned char changed[256];

    for (int i = 0; i <= 255; i++) {
        changed[i] = 255 - i;
    }

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(x, y, qRgb(changed[qRed(pixel)], changed[qGreen(pixel)], changed[qBlue(pixel)]));
        }
    }
}

void ImageModifier::adjustContrast(QImage* image, int contrast) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    double factor = (259.0 * ((double) contrast + 255.0)) / (255.0 * (259.0 - (double) contrast));
    unsigned char changed[256];

    for (int i = 0; i <= 255; i++) {
        changed[i] = trunc((int) (factor * (double) (i - 128)) + 128);
    }

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(x, y, qRgb(changed[qRed(pixel)], changed[qGreen(pixel)], changed[qBlue(pixel)]));
        }
    }
}

void ImageModifier::adjustBrightness(QImage* image, int brightness) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    unsigned char changed[256];

    for (int i = 0; i <= 255; i++) {
        changed[i] = trunc(i + brightness);
    }

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(x, y, qRgb(changed[qRed(pixel)], changed[qGreen(pixel)], changed[qBlue(pixel)]));
        }
    }
}

void ImageModifier::adjustSaturation(QImage *image, int saturation) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    for (int x = 0; x < image->width(); x++) {
        for (int y = 0; y < image->height(); y++) {
            QRgb pixel = image->pixel(x, y);
            QColor color = QColor::fromRgb(pixel);

            int h, s, l;
            color.getHsl(&h, &s, &l);

            s = trunc(s + (saturation * 255 / 100));
            color.setHsl(h, s, l);

            image->setPixel(x, y, color.rgb());
        }
    }
}

void ImageModifier::sumImages(QImage* image1, QImage* image2, double multiplier) {
    for (int x = 0; x < image1->width(); x++) {
        for (int y = 0; y < image1->height(); y++) {
            QRgb pixel1 = image1->pixel(x, y);
            QRgb pixel2 = image2->pixel(x, y);

            int r = trunc(multiplier * (double) (qRed(pixel1) + qRed(pixel2)));
            int g = trunc(multiplier * (double) (qGreen(pixel1) + qGreen(pixel2)));
            int b = trunc(multiplier * (double) (qBlue(pixel1) + qBlue(pixel2)));

            image1->setPixel(x, y, qRgb(r, g, b));
        }
    }
}

void ImageModifier::subtractImages(QImage* image1, QImage* image2) {
    for (int x = 0; x < image1->width(); x++) {
        for (int y = 0; y < image1->height(); y++) {
            QRgb pixel1 = image1->pixel(x, y);
            QRgb pixel2 = image2->pixel(x, y);

            int r = trunc(qRed(pixel1) - qRed(pixel2));
            int g = trunc(qGreen(pixel1) - qGreen(pixel2));
            int b = trunc(qBlue(pixel1) - qBlue(pixel2));

            image1->setPixel(x, y, qRgb(r, g, b));
        }
    }
}

void ImageModifier::multiplyImages(QImage* image1, QImage* image2) {
    for (int x = 0; x < image1->width(); x++) {
        for (int y = 0; y < image1->height(); y++) {
            QRgb pixel1 = image1->pixel(x, y);
            QRgb pixel2 = image2->pixel(x, y);

            int r = trunc((qRed(pixel1) * qRed(pixel2)) / 255);
            int g = trunc((qGreen(pixel1) * qGreen(pixel2)) / 255);
            int b = trunc((qBlue(pixel1) * qBlue(pixel2)) / 255);

            image1->setPixel(x, y, qRgb(r, g, b));
        }
    }
}
