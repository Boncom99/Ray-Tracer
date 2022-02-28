#ifndef TORUS_H
#define TORUS_H
#include "Object.h"
#include "MyVector.h"
#include "Ray.h"
#include "Color.h"
#include "SolveEquation.h"
#include "Surround.h"
class Torus : public Object
{
public:
    MyVector center;
    double R;
    double r;
    MyVector direction;
    Surround surround;
    Torus(MyVector center, double R, double r, MyVector direction, Color c, float roughness);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
};

Torus::Torus(MyVector center, double R, double r, MyVector direction, Color c, float roughness) : Object(c, roughness), center(center), R(R), r(r), direction(direction), surround(Surround(center, R + r))
{
}
MyVector Torus::NormalVector(MyVector position)
{ // TODO supose center != (0,0,0)
    double a = R / (sqrt(position.x * position.x + position.y * position.y));
    MyVector N = position - MyVector(a * position.x, a * position.y, 0);
    N.normalize();
    return N;
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
    if (!surround.hit(ray))
    {
        return -1;
    }
    MyVector originalPosition = ray->position;
    // MyVector originalDirection = ray->direction;
    ray->position = ray->position - center;
    // ray->direction = ray->direction - direction;
    // ray->direction.normalize();
    // double a = ray->direction.moduleSq() * ray->direction.moduleSq();
    double a = 1.0;
    double b = 4 * (dotProduct(ray->position, ray->direction));
    double c = 2 * (ray->position.moduleSq() - r * r - R * R) + 4 * (dotProduct(ray->direction, ray->position) * dotProduct(ray->direction, ray->position)) + 4 * R * R * ray->direction.y * ray->direction.y;
    double d = 4 * (ray->position.moduleSq() - r * r - R * R) * (dotProduct(ray->direction, ray->position)) + 8 * R * R * ray->position.y * ray->direction.y;
    double e = pow(ray->position.moduleSq() - r * r - R * R, 2) - 4 * R * R * (r * r - pow(ray->position.y, 2));
    ray->position = originalPosition;
    // ray->direction = originalDirection;
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