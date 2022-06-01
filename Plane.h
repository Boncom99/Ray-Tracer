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
    Plane(MyVector normal, MyVector point, Color c, float roughness);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    double distance(MyVector p);
};

Plane::Plane(MyVector normal, MyVector point, Color c, float roughness) : Object(c, roughness), normal(normal), point(point)
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
double Plane::distance(MyVector p)
{
    return 0;
}
#endif
