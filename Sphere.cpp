#include "Ray.h"
#include "Sphere.h"
Sphere::Sphere() : Object(Color(0, 0, 0)), center({0, 0, 0}), radius(0)

{
}

Sphere::Sphere(MyVector cent, double rad, Color col) : Object(col), center(cent), radius(rad)
{
}
MyVector Sphere::NormalVector(MyVector position)
{
    MyVector aux(position - center);
    aux.normalize();
    return aux;
}
double Sphere::hit(Ray *ray)
{
    // double a = 1; //direction.moduleSq() //sempre valdrà 1
    double b = 2 * (dotProduct((ray->position - center), ray->direction));
    double c = (ray->position - center).moduleSq() - radius * radius;
    // Discriminant
    double discriminant = b * b - 4 * c;
    if (discriminant >= 0)
    {
        double t2 = (-1 * b - sqrt(discriminant)) / 2.0;
        if (t2 > 0.00001)
        {
            return t2;
        }
        else
        {
            double t1 = (-1 * b + sqrt(discriminant)) / (2.0);
            if (t1 > 0.00001)
            {
                return t1;
            }
        }
    }

    return -1;
}
/*double Sphere::distance(Ray ray, double t)
{
    MyVector aux = ray.getPosition(t) + (center * (-1));
    return aux.module() - radius;
}*/
