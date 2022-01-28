#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <iostream>
#include "Ray.h"
#include "MyVector.h"
class Object
{
public:
    std::vector<int> color;

public:
    virtual double hit(Ray ray) = 0;
    virtual MyVector NormalVector(MyVector position) = 0;
};

#endif