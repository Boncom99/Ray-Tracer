#ifndef Ray_H
#define Ray_H
#include "object.h"
#include "myVector.h"
class Ray
{
public:
    MyVector position;
    MyVector direction;

public:
    Ray(MyVector pos, MyVector dir);
    bool intersection(Sphere sphere);
    MyVector getPosition(double t);
    double distance(double t, Sphere sphere);
    ~Ray();
};

Ray::Ray(MyVector pos, MyVector dir) : position(pos), direction(dir)
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
bool Ray::intersection(Sphere sphere)
{
    double t = 0;
    double d = 1;
    for (int i = 0; i < 500; i++)
    {
        d = this->distance(t, sphere);
        if (d <= 0.0001)
        { //impacten
            direction = sphere.Rebound(this->getPosition(t), direction);
            position = this->getPosition(t);
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