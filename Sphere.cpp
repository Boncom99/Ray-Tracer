#include "Ray.h"
#include "Sphere.h"

Sphere::Sphere(MyVector cent, double rad, Color col, float roughness) : Object(col, roughness), center(cent), radius(rad)
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

    double b = (dotProduct((ray->position - center), ray->direction));
    double c = (ray->position - center).moduleSq() - radius * radius;
    // Discriminant
    double discriminant = b * b - c;
    if (discriminant >= 0)
    {
        double t = (-1 * b - sqrt(discriminant)); // ens quedem amb la primera solució ja que no volem entrar a l'esfera
        if (t > 0.0001)
            return t;
        double t2 = (-1 * b + sqrt(discriminant)); // estem dins l'esfera
        if (t2 > 0.0001)
            return t2;
    }

    return -1;
}
double Sphere::distance(MyVector position)
{

    MyVector dist = center - position;
    return (dist.module() - radius);
}