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

private:
    int trunc(int value);
};

#endif // IMAGEMODIFIER_H
