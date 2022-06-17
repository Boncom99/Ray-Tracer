#ifndef SUBTRACTION_H
#define SUBTRACTION_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>
class Subtraction : public Object
{
public:
    Object *object1;
    Object *object2;

public:
    Subtraction(Object *o1, Object *o2, double r);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    void Rebound(Ray *ray, MyVector hitPosition);
    double distance(MyVector p);
};

#endif