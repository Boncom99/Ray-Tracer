#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <iostream>

class Sphere
{
public:
    MyVector center;
    double radius;
    std::vector<int> color;

public:
    Sphere(/* args */);
    Sphere(MyVector cent, double rad, std::vector<int> col);
    MyVector NormalVector(MyVector position);
    MyVector Rebound(MyVector impactPoint, MyVector ray);
    ~Sphere();
};

Sphere::Sphere(/* args */) : center({0, 0, 0}), radius(0), color({0, 0, 0})

{
}

Sphere::Sphere(MyVector cent, double rad, std::vector<int> col) : center(cent), radius(rad), color(col)
{
}
MyVector Sphere::NormalVector(MyVector position)
{
    MyVector aux(position + center);
    aux.normalize();
    return aux;
}
MyVector Sphere::Rebound(MyVector impactPoint, MyVector ray)
{
    MyVector normalVec = NormalVector(impactPoint);
    //volem descomposar el vector Ray en el component paralel i perpendicular al vector normal
    //li direm u component que pertany al pla tangent i v component ortogonal al pla.
    //v: la projeccio del vec.ray al vector normal és ||ray||*cos(angle) * normal.
    //pero el vector director del ray ja esta normalitzat
    //el cos(angle)= producte escalar
    //u: Ray-v
    MyVector v = dotProduct(ray, normalVec) * normalVec;
    MyVector u = ray + (-1.0 * v);
    MyVector aux = u - v;
    aux.normalize();
    return aux;
}
Sphere::~Sphere()
{
}

#endif