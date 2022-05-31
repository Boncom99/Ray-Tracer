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
double call_foo(Object &obj, Ray *ray) { return obj.hit(ray); }
double Intersection::hit(Ray *ray)
{
    // double a = 1; //direction.moduleSq() //sempre valdrà 1
    std::cout << object1->color.red << std::endl;
    double h1 = call_foo(object1, ray);

    std::cout << "b" << std::endl;
    if (h1 < 0)
        return -1;
    double h2 = object2->hit(ray);
    if (h2 < 0)
        return -1;

    return max(h1, h2);
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
