#ifndef IMAGEMODIFIER_H
#define IMAGEMODIFIER_H

class QImage;

class ImageModifier
{
public:
    ImageModifier();
    int trunc(int value);
    void desaturate(QImage* image);
    void invertColors(QImage* image);
    void adjustContrast(QImage* image, int contrast);
    void adjustBrightness(QImage* image, int brightness);
};

#endif // IMAGEMODIFIER_H
