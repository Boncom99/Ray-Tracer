#include "Ray.h"
#include "Intersection.h"
#include "Color.h"
#include "Sphere.h"

Intersection::Intersection(Object *o1, Object *o2, double r) : Object(o1->color, r), object1(o1), object2(o2)
{
}
MyVector Intersection::NormalVector(MyVector position)
{
    return MyVector(0, 0, 0);
}

double Intersection::distance(MyVector p)
{
    double d1 = object1->distance(p);
    double d2 = object2->distance(p);
    return std::max(d1, d2);
}
double Intersection::hit(Ray *ray)
{
    MyVector position = ray->position;
    double d = this->distance(position);
    double total = d;
    for (int i = 0; i < 100; i++)
    {
        if (d < 0.05)
        {
            return total;
        }
        position += d * ray->direction;
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
