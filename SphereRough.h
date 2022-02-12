#ifndef SPHEREROUGH_H
#define SPHEREROUGH_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "Sphere.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>

class SphereRough : public Sphere
{

public:
    double roughness; // between 0 and 1.
    SphereRough();
    SphereRough(MyVector cent, double rad, Color col);
    SphereRough(MyVector cent, double rad, Color col, double roughness);
    void Rebound(Ray *ray, MyVector hitPosition);
};

SphereRough::SphereRough() : Sphere(), roughness(0) {}
SphereRough::SphereRough(MyVector cent, double rad, Color color) : Sphere(cent, rad, color), roughness(0) {}
SphereRough::SphereRough(MyVector cent, double rad, Color color, double roughness) : Sphere(cent, rad, color), roughness(roughness)
{
}

void SphereRough::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector normalVector = this->NormalVector(hitPosition);
    MyVector v = dotProduct(/*-1 * */ (ray->direction), normalVector) * normalVector;
    MyVector u = ray->direction + (-1.0 * v);
    MyVector refrection = (u - v);
    refrection.normalize();
    double randX = (double)rand() / RAND_MAX;
    double randY = (double)rand() / RAND_MAX;
    double randZ = (double)rand() / RAND_MAX;
    MyVector randomVector(randX, randY, randZ);
    randomVector.normalize();
    ray->direction = refrection + roughness * randomVector;
    ray->position = hitPosition;
}

#endif