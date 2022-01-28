#ifndef Ray_H
#define Ray_H
#include "MyVector.h"
class Ray
{
public:
    MyVector position;
    MyVector direction;
    int bounces;

public:
    Ray(MyVector pos, MyVector dir);
    MyVector getPosition(double t);
    void Rebound(MyVector normalVector, MyVector hitPosition);
};

#endif