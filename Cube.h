#ifndef CUBE_H
#define CUBE_H
#include "Square.h"
#include "Object.h"
#include "Ray.h"
class Cube : public Object
{
public:
    Square base;
    double height;
    Cube();
    Cube(Square base, double height);
    MyVector NormalVector(MyVector position);
    double hit(Ray ray);
};

Cube::Cube() : base(Square()), height(0)
{
}
Cube::Cube(Square base, double height) : base(base), height(height)
#endif