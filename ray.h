#ifndef Ray_H
#define Ray_H
#include "object.h"
#include "myVector.h"
class Ray
{
public:
    MyVector position;
    MyVector direction;
    double time;

public:
    Ray(MyVector pos, MyVector dir);
    bool intersection(Ray r, Sphere sphere);
    MyVector getPosition(double t);
    double distance(double t, Sphere sphere);
    ~Ray();
};

Ray::Ray(MyVector pos, MyVector dir) : position(pos), direction(dir), time(0)
{
    direction.normalize();
}
MyVector Ray::getPosition(double t)
{
    MyVector aux = position + (direction * t);
    return aux;
}

double Ray::distance(double t, Sphere sphere)
{
    MyVector aux = getPosition(t) + (sphere.center * (-1));
    return aux.module() - sphere.radius;
}
bool intersection(Ray r, Sphere sphere)
{
    double t = 0;
    double d = 1;
    for (int i = 0; i < 500; i++)
    {
        d = r.distance(t, sphere);
        if (d <= 0.001)
        {
            return 1;
        }
        else if (d > 500)
        {
            break;
        }
        t += d;
    }

    return 0;
}
Ray::~Ray()
{
}

#endif