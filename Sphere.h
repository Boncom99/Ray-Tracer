#ifndef SPHERE_H
#define SPHERE_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include <iostream>
class Sphere : public Object
{
public:
    MyVector center;
    double radius;
    std::vector<int> color;

public:
    Sphere();
    double distance(Ray ray, double t);
    Sphere(MyVector cent, double rad, std::vector<int> col);
    MyVector NormalVector(MyVector position);
    double hit(Ray ray);
};

#endif