#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <iostream>
#include "Ray.h"
#include "MyVector.h"
#include "Color.h"
class Object
{
protected:
    Object(Color color) : color(color) {}

public:
    Color color;
    virtual double hit(Ray ray) = 0;
    virtual MyVector NormalVector(MyVector position) = 0;
};

#endif