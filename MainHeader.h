#ifndef MAINHEADER_H
#define MAINHEADER_H
#include "MyVector.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Subtraction.h"
#include "Plane.h"
#include "Square.h"
#include "Torus.h"
#include "Color.h"
#include "Eye.h"
#include "Ray.h"
#include "Image.h"
#include "SphereGlass.h"
#include "SphereMoving.h"
#include "Light.h"
#include "Scene.h"
#include <chrono>
#include <algorithm>
#include <iterator>

using namespace std;
double minPositiveTime(vector<double> vec, int n)
{
    int aux = -1;
    double val = 10000;
    for (int i = 0; i < n; i++)
    {
        if (vec[i] < val && vec[i] > 0)
        {
            val = vec[i];
            aux = i;
        }
    }
    return aux;
}
Color PaintPixel(Scene scene, Ray *ray, int Bounces)
{
    if (Bounces <= 0)
    {
        return Color(0, 0, 0);
    }
    bool goesToInfinity = true;
    // Check if ray hits any object
    vector<double> listTimes(scene.size);
    for (int s = 0; s < scene.size; s++) // per cada spheres
    {
        double t = scene.world[s]->hit(ray);
        listTimes[s] = t;
        if (t > 0.0001) // intersecció!
        {
            goesToInfinity = false;
        }
    }
    if (!goesToInfinity)
    {
        double min = minPositiveTime(listTimes, scene.size);
        Object *object;
        object = scene.world[min];

        MyVector impactPos = ray->getPosition(listTimes[min]);
        if (dynamic_cast<Light *>(object) == nullptr) // en cas que impacti amb la font d'iluminació
        {

            SphereGlass *child = dynamic_cast<SphereGlass *>(object);
            JuliaSet *julia = dynamic_cast<JuliaSet *>(object);
            if (child)
                child->Rebound(ray, impactPos);
            else if (julia)
            {
                // MyVector N = object->NormalVector(impactPos);
                return julia->colorize(listTimes[min]);
                // return object->Phong(MyVector(-1, 3, 1), scene.eyePosition, impactPos, N);
            }
            else
                object->Rebound(ray, impactPos);

            return (scene.lightAbsortion * object->color) * PaintPixel(scene, ray, Bounces - 1);
        }
        else
        {
            return object->color;
        }
    }
    return scene.background;
}
#endif