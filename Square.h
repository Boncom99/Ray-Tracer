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
bool nearZero(double a)
{
    if (abs(a) < 0.0001)
        return true;
    return false;
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
        if (nearZero(denominator))
        {
            denominator = v[i] * u[j] - v[j] * u[i];
        }

        if (!nearZero(denominator))
        {
            double b = (u[i] * p[j] - u[j] * p[i]) / denominator;
            if (b >= -0.0001 && b <= 1.0001)
            {
                double a = -1;
                if (!nearZero(u[i]))
                    a = (p[i] - b * v[i]) / u[i];
                else if (!nearZero(u[j]))
                    a = (p[j] - b * v[j]) / u[j];
                if (a >= -0.001 && a <= 1.0001)
                    return t;
            }
        }
    }
    int i = 0;
    int j = 2;

    double denominator = v[j] * u[i] - v[i] * u[j];

    if (nearZero(denominator))
    {
        denominator = v[i] * u[j] - v[j] * u[i];
    }
    if (!nearZero(denominator))
    {
        double b = (u[i] * p[j] - u[j] * p[i]) / denominator;
        if (b >= -0.0001 && b <= 1.0001)
        {
            double a = -1;
            if (!nearZero(u[i]))
                a = (p[i] - b * v[i]) / u[i];
            else if (!nearZero(u[j]))
                a = (p[j] - b * v[j]) / u[j];
            if (a >= -0.0001 && a <= 1.0001)
                return t;
        }
    }

    return -1;
}
#endif
