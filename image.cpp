#include "image.h"
#include "rgbcolor.h"

Image::Image(unsigned short _sizeX, unsigned short _sizeY)
    : sizeX(_sizeX), sizeY(_sizeY)
{
    pixels = new RGBColor*[sizeX];

    for (int x = 0; x < sizeX; x++) {
        pixels[x] = new RGBColor[sizeY];
    }
}

Image::Image(unsigned short _sizeX, unsigned short _sizeY, RGBColor**& _pixels)
    : sizeX(_sizeX), sizeY(_sizeY), pixels(_pixels) {}

unsigned short Image::getSizeX() {
    return sizeX;
}

unsigned short Image::getSizeY() {
    return sizeY;
}
