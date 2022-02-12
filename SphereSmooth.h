#ifndef SPHERESMOOTH_H
#define SPHERESMOOTH_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Sphere.h"
#include "Color.h"
#include <iostream>
class SphereSmooth : public Sphere
{
public:
    SphereSmooth();
    SphereSmooth(MyVector cent, double rad, Color col);
    void Rebound(Ray *ray, MyVector hitPosition);
};

SphereSmooth::SphereSmooth() : Sphere() {}
SphereSmooth::SphereSmooth(MyVector cent, double rad, Color color) : Sphere(cent, rad, color)
{
}

void SphereSmooth::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector normalVector = this->NormalVector(hitPosition);
    MyVector v = dotProduct(/*-1 * */ (ray->direction), normalVector) * normalVector;
    MyVector u = ray->direction + (-1.0 * v);
    ray->direction = (u - v);
    ray->direction.normalize();
    ray->position = hitPosition;
}

#endif