#ifndef IMAGEMODIFIER_H
#define IMAGEMODIFIER_H

class QImage;

class ImageModifier
{
public:
    ImageModifier();
    void desaturate(QImage* image);
    void invertColors(QImage* image);
    void adjustContrast(QImage* image, int contrast);
    void adjustBrightness(QImage* image, int brightness);
    void adjustSaturation(QImage *image, int saturation);

    void sumImages(QImage* image1, QImage* image2, double multiplier);
    void subtractImages(QImage* image1, QImage* image2);
    void multiplyImages(QImage* image1, QImage* image2);

private:
    int trunc(int value);
};

#endif // IMAGEMODIFIER_H
