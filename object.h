#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <iostream>
#include "Ray.h"
#include "MyVector.h"
#include "Color.h"
class Object
{
protected:
    Object(Color color, float roughness) : color(color), roughness(roughness) {}

public:
    Color color;
    float roughness;
    // char typeRebound;
    virtual double hit(Ray *ray) = 0;
    virtual MyVector NormalVector(MyVector position) = 0;
    void Rebound(Ray *ray, MyVector hitPosition)
    {
        MyVector normalVector = this->NormalVector(hitPosition);
        MyVector v = dotProduct(/*-1 * */ (ray->direction), normalVector) * normalVector;
        MyVector refrection = ray->direction - 2 * v;
        refrection.normalize();
        if (roughness != 0)
        {
            double randX = (double)rand() / RAND_MAX;
            double randY = (double)rand() / RAND_MAX;
            double randZ = (double)rand() / RAND_MAX;
            MyVector randomVector(randX, randY, randZ);
            ray->direction = refrection + roughness * randomVector;
        }
        else
        {
            ray->direction = refrection;
        }
        ray->position = hitPosition;
    }
};
#endif