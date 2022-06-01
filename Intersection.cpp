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
double Intersection::distance(MyVector p)
{
    double d1 = object1->distance(p);
    double d2 = object2->distance(p);
    return max(d1, d2);
}
double Intersection::hit(Ray *ray)
{
    MyVector position = ray->position;
    double d = distance(position);
    double total = d;
    for (int i = 0; i < 100; i++)
    {
        if (d < 0.05)
        {
            std::cout << "a";
            return total;
        }
        d = distance(position);
        total += d;
    }
    return -1;
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
