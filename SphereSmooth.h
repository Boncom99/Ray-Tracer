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
    MyVector NormalVector(MyVector position);
};

SphereSmooth::SphereSmooth() : Sphere() {}
SphereSmooth::SphereSmooth(MyVector cent, double rad, Color color) : Sphere(cent, rad, color)
{
}
MyVector SphereSmooth::NormalVector(MyVector position)
{
    MyVector aux(position - center);
    aux.normalize();
    return aux;
}

#endif