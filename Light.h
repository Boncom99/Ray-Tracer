#ifndef LIGHT_H
#define LIGHT_H
#include <vector>
#include "Ray.h"
#include "Object.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>
class Light : public Sphere
{
public:
    MyVector center;
    double radius;
    Light(MyVector center, double radius, Color color);
    void Rebound(Ray *ray, MyVector hitPosition) {}
};

Light::Light(MyVector center, double radius, Color color) : Sphere(center, radius, color)
{
}

#endif
