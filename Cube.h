#ifndef CUBE_H
#define CUBE_H
#include "Square.h"
#include "Object.h"
#include "Ray.h"
class Cube : public Object
{
public:
    Parallelogram base;
    double height;
    Cube();
    Cube(Parallelogram base, double height);
    MyVector NormalVector(MyVector position);
    double hit(Ray ray);
};

Cube::Cube() : base(Parallelogram()), height(0)
{
}
Cube::Cube(Parallelogram base, double height) : base(base), height(height)
#endif