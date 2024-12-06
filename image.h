#ifndef IMAGE_H
#define IMAGE_H

class RGBColor;

class Image
{
public:
    Image(unsigned short _sizeX, unsigned short _sizeY);
    Image(unsigned short _sizeX, unsigned short _sizeY, RGBColor**& _pixels);
    unsigned short sizeX;
    unsigned short sizeY;
    RGBColor** pixels;
};

#endif // IMAGE_H
