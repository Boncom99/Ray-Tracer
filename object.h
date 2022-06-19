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

        if (roughness != 0)
        {
            double randX = rand() % 100 - 50;
            double randY = rand() % 100 - 50;
            double randZ = rand() % 100 - 50;
            MyVector randomVector(randX, randY, randZ);
            randomVector.normalize();
            if (dotProduct(randomVector, ray->direction) < 0.0) // In the same hemisphere as the normal
                ray->direction = randomVector;
            else
                ray->direction = -1 * randomVector;
        }
        else
        {
            MyVector normalVector = this->NormalVector(hitPosition);
            MyVector v = dotProduct(/*-1 * */ (ray->direction), normalVector) * normalVector;
            MyVector refrection = ray->direction - 2 * v;
            refrection.normalize();
            ray->direction = refrection;
        }
        ray->position = hitPosition;
    }
    float max(float a, float b)
    {
        if (a >= b)
            return a;
        return b;
    }
    Color Phong(MyVector light, MyVector eye, MyVector pt, MyVector N)
    {
        Color diffuse = this->color;
        //(1.00, 0.45, 0.25);              // base color of shading
        const int specularExponent = 10; // shininess of shading
        const float specularity = 0.45;  // amplitude of specular highlight
        MyVector E = (eye - pt);         // find the vector to the eye
        E.normalize();
        MyVector L = light - pt; // find the vector to the light
        L.normalize();
        float NdotL = dotProduct(N, L); // find the cosine of the angle between light and normal

        MyVector R = L - 2 * NdotL * N;
        N.absoluteValue(); // find the reflected vector
        N = N * 0.3;
        double b = (specularity * pow(max(dotProduct(E, R), 0), specularExponent));
        diffuse += Color(N.x, N.y, N.z); // add some of the normal to the
        Color a = (max(NdotL, 0.01) * diffuse);
        return Color(a.red + b, a.green + b, a.blue + b);
    }
};
#endif