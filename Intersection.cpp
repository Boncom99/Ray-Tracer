#include "Ray.h"
#include "Intersection.h"
#include "Color.h"
#include "Sphere.h"

Intersection::Intersection(Object *o1, Object *o2) : Object(Color(0, 0, 0), 0), object1(o1), object2(o2)
{
}
MyVector Intersection::NormalVector(MyVector position)
{
    return MyVector(0, 0, 0);
}
double max(double a, double b)
{
    if (a >= b)
        return a;
    return b;
}
double Intersection::hit(Ray *ray)
{
    double h = object1->hit(ray);
    if (h < 0)
        return -1;
    double h2 = object2->hit(ray);
    if (h2 < 0)
        return -1;

    return max(h, h2);
}
void Intersection::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector N1 = object1->NormalVector(hitPosition);
    if (dotProduct(ray->direction, N1) > 0) // ray inside object 1
    {
        object2->Rebound(ray, hitPosition);
        return;
    }
    object1->Rebound(ray, hitPosition);
}
