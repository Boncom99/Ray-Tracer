#ifndef COLOR2_H
#define COLOR2_H
#include <vector>
#include "Color.h"
#include <iostream>
class Color2
{
public:
    float red;
    float green;
    float blue;
    Color2();
    Color2(float red, float green, float blue);

    Color2 &operator+=(const Color2 &c)
    {
        red += c.red;
        green += c.green;
        blue += c.blue;
        return *this;
    }
    Color convertToColor();
    void convertToColor2(Color c);
    void printColor2();
};

Color2::Color2() : red(0), green(0), blue(0)
{
}
Color2::Color2(float red, float green, float blue) : red(red), green(green), blue(blue)
{
}
inline Color2 operator*(double d, const Color2 &c)
{
    return Color2(c.red * d, c.green * d, c.blue * d);
}
inline Color2 operator*(const Color2 &c1, const Color2 &c2)
{
    return Color2(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
}
inline Color2 operator+(const Color2 &c1, const Color2 &c2)
{
    return Color2(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue);
}
Color Color2::convertToColor()
{
    return Color((int)(red * 255), (int)(green * 255), (int)(blue * 255));
}

void Color2::convertToColor2(Color c)
{
    red = (double)c.red / 255.0;
    green = (double)c.green / 255.0;
    blue = (double)c.blue / 255.0;
}
void Color2::printColor2()
{
    std::cout << "red: " << red << ", green: " << green << ", blue: " << blue << "\n";
}

#endif