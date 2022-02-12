#ifndef JULIASET_H
#define JULIASET_H
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
class JuliaSet : public Object
{
public:
    double threshold;
    JuliaSet();
    JuliaSet(double threshold);
    MyVector NormalVector(MyVector position); // null
    double hit(Ray *ray);                     // RayMarching
};

JuliaSet::JuliaSet() : threshold(1)
{
}
JuliaSet::JuliaSet(double threshold) : threshold(threshold)
{
}
MyVector NormalVector(MyVector position)
{
    // aproximar la normal.
    // una altre opció és els rajos no rebotin i calcular el color depenent del numero de passos que ha fet el raig per arribar fins el punt.

    return MyVector();
}
double JuliaSet::hit(Ray *ray)
{

    // fer primer una esfera que envolti a tot el conjunt, aixi els punts de fora ens els estalviem
    // raymarcher
    return -1;
}

#endif