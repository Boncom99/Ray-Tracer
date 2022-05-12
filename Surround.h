#ifndef SURROUND_H
#define SURROUND_H
#include "Ray.h"
#include "MyVector.h"
class Surround
{
    MyVector center;
    float radius;

public:
    Surround(MyVector c, float r);
    bool hit(Ray *ray);
};

Surround::Surround(MyVector c, float r) : center(c), radius(r)
{
}
bool Surround::hit(Ray *ray)
{
    double b = (dotProduct((ray->position - center), ray->direction));
    double c = (ray->position - center).moduleSq() - radius * radius;
    // Discriminant
    double discriminant = b * b - c;
    if (discriminant >= 0)
    {
        double t = (-1 * b - sqrt(discriminant)); // ens quedem amb la primera solució ja que no volem entrar a l'esfera
        if (t > 0.00001)
            return true;
        double t2 = (-1 * b + sqrt(discriminant)); // estem dins l'esfera
        if (t2 > 0.00001)
            return true;
    }

    return false;
}

#endif