#ifndef IMAGE_H
#define IMAGE_H

class RGBColor;

class Image
{
public:
    Image(unsigned short _sizeX, unsigned short _sizeY);
    Image(unsigned short _sizeX, unsigned short _sizeY, RGBColor**& _pixels);
    RGBColor** pixels;
    unsigned short getSizeX();
    unsigned short getSizeY();

private:
    unsigned short sizeX;
    unsigned short sizeY;
};

#endif // IMAGE_H
