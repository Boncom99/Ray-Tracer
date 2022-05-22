#ifndef JULIASET_H
#define JULIASET_H
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Quaternion.h"
class JuliaSet : public Object
{
public:
    double fixedK;

    JuliaSet();
    JuliaSet(double k);
    Quaternion f(Quaternion x);
    double hit(Ray *ray); // RayMarching
    MyVector NormalVector(MyVector position);
};
JuliaSet::JuliaSet() : Object(Color(0.6, 0.6, 0.8), 0), fixedK(0)
{
}
JuliaSet::JuliaSet(double k) : Object(Color(0.6, 0.6, 0.8), 0), fixedK(k)
{
}
Quaternion JuliaSet::f(Quaternion x)
{
    Quaternion c(1, 2, 0, 0);
    return (product(x, x)) + c;
}
void iterate(Quaternion z, Quaternion dz)
{
    Quaternion c(-0.5, 0, 0, 0);
    for (int i = 0; i < 1024; i++)
    {
        dz = 2.0 * product(z, dz);
        z = product(z, z) + c;
        if (z.QModule() > 2)
            break;
    }
}

double JuliaSet::hit(Ray *ray)
{
    Quaternion rayDirection = from3Dto4D(ray->direction, fixedK);
    Quaternion rayPosition = from3Dto4D(ray->position, fixedK);
    Quaternion p0(1, 0, 0, 0);
    for (int count = 0; count < 20; count++)
    {
        Quaternion *z = &rayPosition;
        Quaternion *dz = &p0;
        iterate(*z, *dz);
        float normZ = z->QModule();
        float dist = 0.5 * normZ * log(normZ) / dz->QModule(); // lower bound on distance to surface
        rayPosition += rayDirection * dist;
        // std::cout << d << std::endl;
        if (dist < 0.1)
        {
            std::cout << "in";
            // return totalDistance;
            return count;
        }
        if (dist > 1000)
            return -1;
    }
    // std::cout << "---------_" << std::endl;
    return -1;
}
MyVector JuliaSet::NormalVector(MyVector position)
{
    return MyVector(0, 0, 0);
}
#endif