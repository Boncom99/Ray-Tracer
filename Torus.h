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
    MyVector NormalVector(MyVector position);
    void Rebound(Ray *ray, MyVector hitPosition);
    double hit(Ray *ray);
};

Torus::Torus() : Object(), center(MyVector()), R(0), r(0)
{
}
Torus::Torus(MyVector center, double R, double r, Color c) : Object(c), center(center), R(R), r(r) {}
MyVector Torus::NormalVector(MyVector position)
{
    double a = R / (sqrt(position.x * position.x + position.y * position.y));
    MyVector N = position - MyVector(a * position.x, a * position.y, 0);
    N.normalize();
    return N;
}
void Torus::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector normalVector = this->NormalVector(hitPosition);
    MyVector v = dotProduct(/*-1* */ (ray->direction), normalVector) * normalVector;
    ray->direction = ray->direction - 2 * v;
    ray->direction.normalize();
    ray->position = hitPosition;
}
double minPositive(double s[4])
{
    double aux = 10000;
    for (int i = 0; i < 4; i++)
    {
        if (s[i] > 0.00001 && s[i] < aux)
        {
            aux = s[i];
        }
    }
    if (aux < 10000)
    {
        return aux;
    }
    return -1;
}
double Torus::hit(Ray *ray)
{
    // double a = ray->direction.moduleSq() * ray->direction.moduleSq();
    double a = 1.0;
    double b = 4 * (dotProduct(ray->position, ray->direction));
    double c = 2 * (ray->position.moduleSq() - r * r - R * R) + 4 * (dotProduct(ray->direction, ray->position) * dotProduct(ray->direction, ray->position)) + 4 * R * R * ray->direction.y * ray->direction.y;
    double d = 4 * (ray->position.moduleSq() - r * r - R * R) * (dotProduct(ray->direction, ray->position)) + 8 * R * R * ray->position.y * ray->direction.y;
    double e = pow(ray->position.moduleSq() - r * r - R * R, 2) - 4 * R * R * (r * r - pow(ray->position.y, 2));
    double coefs[5] = {e, d, c, b, a};
    // std::cout << coefs[0] << ", " << coefs[1] << ", " << coefs[2] << ", " << coefs[3] << ", " << coefs[4] << "\n";
    double s[4] = {0, 0, 0, 0};
    int NumOfSolutions = SolveQuartic(coefs, s);
    if (NumOfSolutions == 0)
    {
        return -1;
    }
    // std::cout << aaa << " solutions reals: " << s[0] << ", " << s[1] << ", " << s[2] << ", " << s[3] << "-->";
    double m = minPositive(s);
    // std::cout << m << "\n";
    return m;
}

#endif