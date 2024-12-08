#ifndef IMAGEMODIFIER_H
#define IMAGEMODIFIER_H

class QImage;

class ImageModifier
{
public:
    ImageModifier();
    void desaturate(QImage* image);
};

#endif // IMAGEMODIFIER_H
