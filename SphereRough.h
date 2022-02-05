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
    MyVector NormalVector(MyVector position);
};

SphereRough::SphereRough() : Sphere(), roughness(0) {}
SphereRough::SphereRough(MyVector cent, double rad, Color color) : Sphere(cent, rad, color), roughness(0) {}
SphereRough::SphereRough(MyVector cent, double rad, Color color, double roughness) : Sphere(cent, rad, color), roughness(roughness)
{
}
MyVector SphereRough::NormalVector(MyVector position)
{
    MyVector aux(position - center);
    aux.normalize();
    double randX = (double)rand() / RAND_MAX;
    double randY = (double)rand() / RAND_MAX;
    double randZ = (double)rand() / RAND_MAX;
    MyVector randomVector(randX, randY, randZ);
    randomVector.normalize();
    MyVector returnVector = aux + roughness * randomVector;
    returnVector.normalize();
    return returnVector;
}

#endif