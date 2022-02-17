#ifndef PLANE_H
#define PLANE_H
#include "MyVector.h"
#include "Object.h"
#include "Ray.h"
class Plane : public Object
{
public:
    MyVector normal;
    MyVector point;
    Plane(MyVector normal, MyVector point, Color c);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    void Rebound(Ray *ray, MyVector hitPosition);
};

Plane::Plane(MyVector normal, MyVector point, Color c) : Object(c), normal(normal), point(point)
{
    normal.normalize();
}
MyVector Plane::NormalVector(MyVector position)
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
    double t = (dotProduct(normal, point) - dotProduct(normal, ray->position)) / prodEscalarND;
    if (t > 0.0001)
    {
        return t;
    }
    return -1;
}
void Plane::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector NormalVec = normal;
    // caldria reorientar el vector normal. per si el raig ve per sota el pla
    if (dotProduct(ray->direction, normal) > 0)
    {
        NormalVec = -1 * normal;
    }
    MyVector v = -1 * (dotProduct(ray->direction, NormalVec) * NormalVec);
    ray->direction = ray->direction - 2 * v;
    ray->direction.normalize();
    ray->position = hitPosition;
}

#endif
