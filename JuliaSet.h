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
    Quaternion c;

    JuliaSet();
    JuliaSet(double k, Quaternion c);
    Quaternion f(Quaternion x);
    double hit(Ray *ray); // RayMarching
    MyVector NormalVector(MyVector position);
    void iterate(Quaternion &z, Quaternion &dz);
};
JuliaSet::JuliaSet() : Object(Color(0.8, 0.6, 0.5), 0), fixedK(0), c(Quaternion(-0.5, 0.2, 0.1, 0))
{
}
JuliaSet::JuliaSet(double k, Quaternion c) : Object(Color(0.6, 0.6, 0.8), 0), fixedK(k), c(c)
{
}
Quaternion JuliaSet::f(Quaternion x)
{
    return (product(x, x)) + c;
}
void JuliaSet::iterate(Quaternion &z, Quaternion &dz)
{
    for (int i = 0; i < 1024; i++)
    {
        dz = 2.0 * product(z, dz);
        z = product(z, z) + c;
        if (z.QModuleSq() > 2.8)
            break;
    }
}

double JuliaSet::hit(Ray *ray)
{
    Quaternion rayDirection = from3Dto4D(ray->direction, fixedK);
    Quaternion rayPosition = from3Dto4D(ray->position, fixedK);
    for (int count = 0; count < 600; count++)
    {
        Quaternion z = rayPosition;
        Quaternion dz(1, 0, 0, 0);
        iterate(z, dz);

        float normZ = z.QModule();
        float dist = 0.5 * normZ * log(normZ) / dz.QModule(); // lower bound on distance to surface
        rayPosition += rayDirection * dist;
        // std::cout << d << std::endl;
        if (dist < 0.000001)
        {
            //  return totalDistance;
            return count;
        }
        if (dist > 1000)
            return -1;
    }
    return -1;
}
MyVector JuliaSet::NormalVector(MyVector position)
{
    return MyVector(0, 0, 0);
}
#endif