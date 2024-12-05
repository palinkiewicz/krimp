#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor
{
public:
    RGBColor(_r, _g, _b);
    unsigned char getR();
    unsigned char getG();
    unsigned char getB();

private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif // RGBCOLOR_H
