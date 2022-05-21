#ifndef SPHEREMOVING_H
#define SPHEREMOVING_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "Sphere.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>

class SphereMoving : public Sphere
{

public:
    MyVector initialPosition;
    MyVector finalPosition;
    float time;
    SphereMoving(MyVector cent, double rad, Color col, MyVector iPosition, MyVector fPosition, float time);
    void Rebound(Ray *ray, MyVector hitPosition);
    void trajectory(double t);
    double hit(Ray *ray);
};

SphereMoving::SphereMoving(MyVector cent, double rad, Color col,MyVector iPosition,  MyVector fPosition, float time) : Sphere(cent, rad, col, 1),initialPosition(iPosition), finalPosition(fPosition),time(time) {}

void SphereMoving::trajectory(double t){
    this->center= (1-t)*this->initialPosition+ t*finalPosition;
}
double SphereMoving::hit(Ray *ray)
{
    if(time!=0){
    float random=(float)rand()/RAND_MAX;
    trajectory(random*time);
    }
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
#endif