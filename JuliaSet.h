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
    for (int count = 0; count < 300; count++)
    {
        Quaternion z = rayPosition;
        Quaternion dz(1, 0, 0, 0);
        iterate(z, dz);

        float normZ = z.QModule();
        float dist = 0.5 * normZ * log(normZ) / dz.QModule(); // lower bound on distance to surface
        rayPosition += rayDirection * dist;
        // std::cout << d << std::endl;
        if (dist < 0.00001)
        {
            //  return totalDistance;
            return count;
        }
        if (dist > 100)
            return -1;
    }
    return -1;
}
MyVector normEstimate(MyVector p, Quaternion c, int maxIterations)
{
    const double delta = 0.0001;
    MyVector N;
    Quaternion qP(p, 0);
    float gradX, gradY, gradZ;
    Quaternion gx1 = qP - Quaternion(delta, 0, 0, 0);
    Quaternion gx2 = qP + Quaternion(delta, 0, 0, 0);
    Quaternion gy1 = qP - Quaternion(0, delta, 0, 0);
    Quaternion gy2 = qP + Quaternion(0, delta, 0, 0);
    Quaternion gz1 = qP - Quaternion(0, 0, delta, 0);
    Quaternion gz2 = qP + Quaternion(0, 0, delta, 0);
    for (int i = 0; i < maxIterations; i++)
    {
        gx1 = Qsq(gx1) + c;
        gx2 = Qsq(gx2) + c;
        gy1 = Qsq(gy1) + c;
        gy2 = Qsq(gy2) + c;
        gz1 = Qsq(gz1) + c;
        gz2 = Qsq(gz2) + c;
    }
    gradX = gx2.QModule() - gx1.QModule();
    gradY = gy2.QModule() - gy1.QModule();
    gradZ = gz2.QModule() - gz1.QModule();
    N = MyVector(gradX, gradY, gradZ);
    N.normalize();
    return N;
}
MyVector JuliaSet::NormalVector(MyVector position)
{
    return normEstimate(position, c, 30);
}
#endif