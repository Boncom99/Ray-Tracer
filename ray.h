#ifndef Ray_H
#define Ray_H
#include "myVector.h"
class Ray
{
public:
    MyVector direction;

public:
    Ray();
    Ray(int x, int y, int z);
    ~Ray();
};

Ray::Ray()
{
}

Ray::Ray(int x, int y, int z)
{
    direction.x = x;
    direction.y = y;
    direction.z = z;
}

Ray::~Ray()
{
}

#endif