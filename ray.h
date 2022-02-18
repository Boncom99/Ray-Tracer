#ifndef Ray_H
#define Ray_H
#include "MyVector.h"
#include "Eye.h"
class Ray
{
public:
    MyVector position;
    MyVector direction;

public:
    Ray(MyVector pos, MyVector dir);
    Ray(Eye *eye, MyVector currentPixel);
    MyVector getPosition(double t);
};

#endif