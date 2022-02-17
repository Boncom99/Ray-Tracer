#ifndef SQUARE_H
#define SQUARE_H
#include "MyVector.h"
#include "Plane.h"
#include "Ray.h"
// Like plane, we need to limit the plane somehow
// maybe make it a child of plane
class Square : public Plane
{
public:
    MyVector base;
    MyVector height;
    Square(MyVector base, MyVector height, MyVector point, Color c);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    void Rebound(Ray *ray, MyVector hitPosition);
};

Square::Square(MyVector base, MyVector height, MyVector point, Color c) : Object(c), base(base), height(height), point(point), normal(crossProduct(base, height))
{
    normal.normalize();
}
MyVector Square::NormalVector(MyVector position) // TODO orientar el vector normal
{
    return normal;
}
double Square::hit(Ray *ray)
{
    double prodEscalarND = dotProduct(normal, ray->direction);
    if (abs(prodEscalarND) < 0.001)
    {
        return -1;
    }
    // punt en el que el ray talla el pla. cal veure si està dins del rectangle.
    double t = (dotProduct(normal, point) - dotProduct(normal, ray->position)) / prodEscalarND;
    if (t > 0.0001)
    {
        return t;
    }
    return -1;
}
void Square::Rebound(Ray *ray, MyVector hitPosition)
{

    MyVector v = dotProduct(/*-1* */ (ray->direction), normal) * normal;
    ray->direction = ray->direction - 2 * v;
    ray->direction.normalize();
    ray->position = hitPosition;
}

#endif
