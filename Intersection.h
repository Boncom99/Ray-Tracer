#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>
class Intersection : public Object
{
public:
    Object *object1;
    Object *object2;

public:
    Intersection(Object *o1, Object *o2);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    void Rebound(Ray *ray, MyVector hitPosition);
};

#endif