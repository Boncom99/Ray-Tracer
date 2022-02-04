#include "Color.h"
Color::Color() : red(0), green(0), blue(0)
{
}
Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue)
{
}
Color MitjanaColors2(std::vector<Color> c, int size)
{
    int r = 0;
    int g = 0;
    int b = 0;
    for (int i = 0; i < size; i++)
    {
        r += c[i].red;
        g += c[i].green;
        b += c[i].blue;
    }
    return Color(r / size, g / size, b / size);
}
void Color::printColor()
{
    std::cout << "red: " << red << ", green: " << green << ", blue: " << blue << "\n";
}