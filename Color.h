#ifndef COLOR_H
#define COLOR_H
#include <vector>
#include <iostream>
class Color
{
public:
    float red;
    float green;
    float blue;
    Color();
    Color(float red, float green, float blue);
    friend Color operator*(float d, const Color &c);
    friend Color operator*(const Color &c1, const Color &c2);
    friend Color operator+(const Color &c1, const Color &c2);
    Color &operator+=(const Color &c)
    {
        red += c.red;
        green += c.green;
        blue += c.blue;
        return *this;
    }
    void printColor();
};

#endif