#ifndef SPHERE_H
#define SPHERE_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>
class Sphere : public Object
{
public:
    MyVector center;
    double radius;

public:
    Sphere();
    Sphere(MyVector cent, double rad, Color col);
    // double distance(Ray ray, double t); // not using it
    MyVector NormalVector(MyVector position);
    double hit(Ray ray);
    // virtual void Rebound(Ray *ray, MyVector hitPosition) = 0:
};

#endif