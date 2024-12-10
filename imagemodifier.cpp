#include "imagemodifier.h"
#include <QImage>
#include <QDebug>

ImageModifier::ImageModifier() {}

int ImageModifier::trunc(int value) {
    return qMax(qMin(value, 255), 0);
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

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(x, y, qRgb(255 - qRed(pixel), 255 - qGreen(pixel), 255 - qBlue(pixel)));
        }
    }
}

void ImageModifier::adjustContrast(QImage* image, int contrast) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    double factor = (259.0 * ((double) contrast + 255.0)) / (255.0 * (259.0 - (double) contrast));

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(
                x,
                y,
                qRgb(
                    trunc((int) (factor * (double) (qRed(pixel) - 128)) + 128),
                    trunc((int) (factor * (double) (qGreen(pixel) - 128)) + 128),
                    trunc((int) (factor * (double) (qBlue(pixel) - 128)) + 128)
                    )
                );
        }
    }
}

void ImageModifier::adjustBrightness(QImage* image, int brightness) {
    if (image == nullptr || image->isNull()) {
        return;
    }

    for (int x = 0; x < image->size().width(); x++) {
        for (int y = 0; y < image->size().height(); y++) {
            QRgb pixel = image->pixel(x, y);
            image->setPixel(
                x,
                y,
                qRgb(
                    trunc(qRed(pixel) + brightness),
                    trunc(qGreen(pixel) + brightness),
                    trunc(qBlue(pixel) + brightness)
                    )
                );
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

            s = qBound(0, s + (saturation * 255 / 100), 255);
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
