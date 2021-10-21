#ifndef Ray_H
#define Ray_H
#include "myVector.h"
class Ray
{
public:
    MyVector position;
    MyVector direction;

public:
    Ray();
    Ray(MyVector pos, MyVector dir);
    Ray(int x, int y, int z, int x2, int y2, int z2);
    ~Ray();
};

Ray::Ray()
{
}
Ray::Ray(MyVector pos, MyVector dir) : position(pos), direction(dir)
{
}

Ray::Ray(int x, int y, int z, int x2, int y2, int z2)
{
    position.x = x;
    position.y = y;
    position.z = z;
    direction.x = x2;
    direction.y = y2;
    direction.z = z2;
}

Ray::~Ray()
{
}

#endif