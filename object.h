#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <iostream>

class Sphere
{
public:
    MyVector center;
    double radius;
    std::vector<int> color;

public:
    Sphere(/* args */);
    Sphere(MyVector cent, double rad, std::vector<int> col);
    ~Sphere();
};

Sphere::Sphere(/* args */) : center({0, 0, 0}), radius(0), color({0, 0, 0})

{
}

Sphere::Sphere(MyVector cent, double rad, std::vector<int> col) : center(cent), radius(rad), color(col)
{
}
Sphere::~Sphere()
{
}

#endif