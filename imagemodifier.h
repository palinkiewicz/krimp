#ifndef IMAGEMODIFIER_H
#define IMAGEMODIFIER_H

class QImage;

class ImageModifier
{
public:
    ImageModifier();
    void desaturate(QImage* image);
    void invertColors(QImage* image);
};

#endif // IMAGEMODIFIER_H
