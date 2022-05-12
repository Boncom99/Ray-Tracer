#include "Color.h"
Color::Color() : red(0), green(0), blue(0)
{
}
Color::Color(float red, float green, float blue) : red(red), green(green), blue(blue)
{
}

Color operator*(float d, const Color &c)
{
    return Color(c.red * d, c.green * d, c.blue * d);
}
Color operator*(const Color &c1, const Color &c2)
{
    return Color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
}
inline Color operator+(const Color &c1, const Color &c2)
{
    return Color(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue);
}

void Color::printColor()
{
    std::cout << "red: " << red << ", green: " << green << ", blue: " << blue << "\n";
}