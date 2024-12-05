#include "rgbcolor.h"

RGBColor::RGBColor(unsigned char _r, unsigned char _g, unsigned char _b)
    : r(_r), g(_g), b(_b) {}

unsigned char RGBColor::getR() {
    return r;
}

unsigned char RGBColor::getG() {
    return g;
}

unsigned char RGBColor::getB() {
    return b;
}
