#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor
{
public:
    RGBColor();
    RGBColor(unsigned char _r, unsigned char _g, unsigned char _b);
    unsigned char getR();
    unsigned char getG();
    unsigned char getB();

private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif // RGBCOLOR_H
