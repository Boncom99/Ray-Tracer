#ifndef TORUS_H
#define TORUS_H
#include "Object.h"
#include "MyVector.h"
#include "Ray.h"
#include "Color.h"
#include "Complex.h"
class Torus : public Object
{
public:
    MyVector center;
    double R;
    double r;
    Torus();
    Torus(MyVector center, double R, double r, Color c);
    double Hit(Ray *ray);
};

Torus::Torus() : Object(), center(MyVector()), R(0), r(0)
{
}
Torus::Torus(MyVector center, double R, double r, Color c) : Object(c), center(center), R(R), r(r) {}
double Solve(double A, double B, double C, double D, double E)
{
    Complex a(A, 0);
    Complex b(B, 0);
    Complex c(C, 0);
    Complex d(D, 0);
    Complex e(E, 0);
    Complex Disc = 256 * a * a * a * e * e * e - 192 * a * a * b * d * e * e - 128 * a * a * c * c * e * e + 144 * a * a * c * d * d * e - 27 * a * a * d * d * d * d + 144 * a * b * b * c * e * e - 6 * a * b * b * d * d * e - 80 * a * b * c * c * d * e;
    Disc += 18 * a * b * c * d * d * d + 16 * a * c * c * c * c * e - 4 * a * c * c * c * d * d - 27 * b * b * b * b * e * e + 18 * b * b * b * c * d * e - 4 * b * b * b * d * d * d - 4 * b * b * c * c * c * e + b * b * c * c * d * d;
    return Disc.r;
}
double Torus::Hit(Ray *ray)
{
    double a = ray->direction.moduleSq() * ray->direction.moduleSq();
    double b = 4 * ray->direction.moduleSq() * (dotProduct(ray->position, ray->direction));
    double c = 2 * ray->direction.moduleSq() * (ray->position.moduleSq() - r * r - R * R) + 4 * (dotProduct(ray->direction, ray->position) * dotProduct(ray->direction, ray->position)) + 4 * R * R * ray->direction.y * ray->direction.y;
    double d = 4 * (ray->position.moduleSq() - r * r - R * R) * (dotProduct(ray->direction, ray->position)) + 8 * R * R * ray->position.y * ray->direction.y;
    double e = pow(ray->position.moduleSq() - r * r - R * R, 2) - 4 * R * R * (r * r - pow(ray->position.y, 2));
    return Solve(a, b, c, d, e);
}

#endif