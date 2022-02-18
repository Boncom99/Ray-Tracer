#ifndef SQUARE_H
#define SQUARE_H
#include "MyVector.h"
#include "Plane.h"
#include "Ray.h"
class Parallelogram : public Plane
{
public:
    MyVector u;
    MyVector v;
    Parallelogram(MyVector u, MyVector v, MyVector point, Color c, float roughness);
    double hit(Ray *ray);
};

Parallelogram::Parallelogram(MyVector u, MyVector v, MyVector point, Color c, float roughness) : Plane(crossProduct(u, v), point, c, roughness), u(u), v(v)
{
}

double Parallelogram::hit(Ray *ray)
{
    double t = Plane(normal, point, color, 0).hit(ray);
    if (t == -1)
    {
        return -1;
    }
    MyVector p = ray->getPosition(t) - point;
    for (int i = 0; i < 2; i++)
    {
        int j = (i + 1);

        double denominator = v[j] * u[i] - v[i] * u[j];
        if (denominator != 0)
        {
            double b = (u[i] * p[j] - u[j] * p[i]) / denominator;
            if (b >= 0 && b <= 1)
            {
                double a = (p[i] - b * v[i]) / u[i];
                if (a >= 0 && a <= 1)
                    return t;
            }
        }
    }
    int i = 3;
    int j = 0;

    double denominator = v[j] * u[i] - v[i] * u[j];
    if (denominator != 0)
    {
        double b = (u[i] * p[j] - u[j] * p[i]) / denominator;
        if (b >= 0 && b <= 1)
        {
            double a = (p[i] - b * v[i]) / u[i];
            if (a >= 0 && a <= 1)
                return t;
        }
    }

    return -1;
}
#endif
