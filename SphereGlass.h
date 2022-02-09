#ifndef SPHERESMOOTH_H
#define SPHERESMOOTH_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Sphere.h"
#include "Color.h"
#include <iostream>
class SphereGlass : public Sphere
{
public:
    float refractionIndex;
    SphereGlass();
    SphereGlass(MyVector cent, double rad, Color col, float refractionIndex);
    // MyVector RefractionDirection(Ray ray);
    void Rebound(Ray *ray, MyVector hitPosition);
};

SphereGlass::SphereGlass() : Sphere(), refractionIndex(1) {}
SphereGlass::SphereGlass(MyVector cent, double rad, Color color, float refractionIndex) : Sphere(cent, rad, color), refractionIndex(refractionIndex)
{
}
void SphereGlass::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector normalVector = this->NormalVector(hitPosition);
    double cosTheta = dotProduct(ray->direction, normalVector);
    MyVector v = cosTheta * normalVector;
    MyVector u = ray->direction + (-1.0 * v);
    MyVector reflexion = (u - v).normalize();
    MyVector refraction();

    // ray->direction = (u - v);
    ray->direction.normalize();
    ray->position = hitPosition;
    ray->bounces++;
}

#endif