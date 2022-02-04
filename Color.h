#ifndef COLOR_H
#define COLOR_H
#include <vector>
#include <iostream>
class Color
{
public:
    int red;
    int green;
    int blue;
    Color();
    Color(int red, int green, int blue);
    void printColor();
};
Color MitjanaColors2(std::vector<Color> c, int size);

#endif