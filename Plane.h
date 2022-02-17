#ifndef PLANE_H
#define PLANE_H
#include "MyVector.h"
#include "Object.h"
#include "Ray.h"
class Plane : public Object
{
public:
    MyVector base;
    MyVector height;
    MyVector point;
    MyVector normal;
    Plane(MyVector base, MyVector height, MyVector point, Color c);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    void Rebound(Ray *ray, MyVector hitPosition);
};

Plane::Plane(MyVector base, MyVector height, MyVector point, Color c) : Object(c), base(base), height(height), point(point), normal(crossProduct(base, height))
{
    normal.normalize();
}
MyVector Plane::NormalVector(MyVector position) // TODO orientar el vector normal
{
    return normal;
}
double Plane::hit(Ray *ray)
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
void Plane::Rebound(Ray *ray, MyVector hitPosition)
{

    MyVector v = -1 * (dotProduct(ray->direction, normal) * normal);
    ray->direction = ray->direction - 2 * v;
    ray->direction.normalize();
    ray->position = hitPosition;
}

#endif
