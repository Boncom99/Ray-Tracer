#ifndef Ray_H
#define Ray_H
#include "object.h"
#include "myVector.h"
class Ray
{
public:
    MyVector position;
    MyVector direction;
    int bounces;

public:
    Ray(MyVector pos, MyVector dir);
    double intersection(Sphere sphere);
    MyVector getPosition(double t);
    double distance(double t, Sphere sphere);
    ~Ray();
};

Ray::Ray(MyVector pos, MyVector dir) : position(pos), direction(dir), bounces(0)
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
double Ray::intersection(Sphere sphere) //no retorna cap numero negatiu
{
    double a = 1; //direction.moduleSq() //sempre valdrà 1
    double b = 2 * (dotProduct((position - sphere.center), direction));
    double c = (position - sphere.center).moduleSq() - sphere.radius * sphere.radius;
    //Discriminant
    double discrim = b * b - 4 * a * c;
    if (discrim >= 0)
    {
        double t2 = (-1 * b - sqrt(discrim)) / (2 * a);
        if (t2 > 0.1)
        {
            return t2;
        }
        else
        {
            double t1 = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a);
            if (t1 > 0.1)
            {
                return t1;
            }
        }
    }

    return -1;
}
Ray::~Ray()
{
}

#endif