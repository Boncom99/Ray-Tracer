#ifndef TORUS_H
#define TORUS_H
#include "Object.h"
#include "MyVector.h"
#include "Ray.h"
#include "Color.h"
#include "Complex.h"
#include "SolveEquation.h"
class Torus : public Object
{
public:
    MyVector center;
    double R;
    double r;
    Torus();
    Torus(MyVector center, double R, double r, Color c);
    MyVector NormalVector(MyVector position) { return MyVector(); };
    void Rebound(Ray *ray, MyVector hitPosition){};
    double hit(Ray *ray);
};

Torus::Torus() : Object(), center(MyVector()), R(0), r(0)
{
}
Torus::Torus(MyVector center, double R, double r, Color c) : Object(c), center(center), R(R), r(r) {}

double Torus::hit(Ray *ray)
{
    // double a = ray->direction.moduleSq() * ray->direction.moduleSq();
    double a = 1.0;
    double b = 4 * ray->direction.moduleSq() * (dotProduct(ray->position, ray->direction));
    double c = 2 * ray->direction.moduleSq() * (ray->position.moduleSq() - r * r - R * R) + 4 * (dotProduct(ray->direction, ray->position) * dotProduct(ray->direction, ray->position)) + 4 * R * R * ray->direction.y * ray->direction.y;
    double d = 4 * (ray->position.moduleSq() - r * r - R * R) * (dotProduct(ray->direction, ray->position)) + 8 * R * R * ray->position.y * ray->direction.y;
    double e = pow(ray->position.moduleSq() - r * r - R * R, 2) - 4 * R * R * (r * r - pow(ray->position.y, 2));
    double coefs[5] = {e, d, c, b, a};
    double s[4] = {0, 0, 0, 0};
    SolveQuartic(coefs, s);
    std::cout << s[0] << ", " << s[1] << ", " << s[2] << ", " << s[3] << "\n";

    return 3.0;
}

#endif