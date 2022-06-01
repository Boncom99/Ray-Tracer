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
    Object(Color col, float roughness) : color(col), roughness(roughness) {}

public:
    Color color;
    float roughness;
    // char typeRebound;
    virtual double hit(Ray *ray) = 0;
    virtual MyVector NormalVector(MyVector position) = 0;
    virtual double distance(MyVector position) = 0;
    void Rebound(Ray *ray, MyVector hitPosition)
    {

        MyVector normalVector = this->NormalVector(hitPosition);
        if (roughness != 0)
        {
            double randX = rand() % 100 - 50;
            double randY = rand() % 100 - 50;
            double randZ = rand() % 100 - 50;
            MyVector randomVector(randX, randY, randZ);
            randomVector.normalize();
            if (dotProduct(randomVector, normalVector) > 0.0) // In the same hemisphere as the normal
                ray->direction = randomVector;
            else
                ray->direction = -1 * randomVector;
        }
        else
        {
            MyVector v = dotProduct(/*-1 * */ (ray->direction), normalVector) * normalVector;
            MyVector refrection = ray->direction - 2 * v;
            refrection.normalize();
            ray->direction = refrection;
        }
        ray->position = hitPosition;
    }
};
#endif