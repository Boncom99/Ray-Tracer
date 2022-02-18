#include "MyVector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Square.h"
#include "Torus.h"
#include "Color.h"
#include "Color2.h"
#include "Eye.h"
#include "Ray.h"
#include "Image.h"
#include "SphereGlass.h"
#include "Light.h"
#include <map>

using namespace std;

Color2 PaintPixel(Object **objects, int size, Ray *ray, int Bounces)
{
    if (Bounces <= 0)
    {
        return Color2(0, 0, 0);
    }
    bool goesToInfinity = true;
    // Check if ray hits any object
    map<Object *, double> listObjects; // list where we keep all objects that intersects with ray
    for (int s = 0; s < size; s++)     // per cada spheres
    {
        double t = objects[s]->hit(ray);
        if (t > 0.0001) // intersecció!
        {
            goesToInfinity = false;
            listObjects[objects[s]] = t;
        }
    }
    if (!goesToInfinity)
    {
        auto object = min_element(listObjects.begin(), listObjects.end(), // escollim l'objecte amb que primer intersecciona amb el raig
                                  [](const auto &l, const auto &r)
                                  { return l.second < r.second; });
        MyVector auxPos = ray->getPosition(object->second);
        if (dynamic_cast<Light *>(object->first) == nullptr) // en cas que impacti amb la font d'iluminació
        {
            object->first->Rebound(ray, auxPos);
            return (0.5 * convertToColor2(object->first->color)) * PaintPixel(objects, size, ray, Bounces - 1);
        }
        else
        {
            return convertToColor2(object->first->color);
        }
    }
    return Color2(0.1, 0.2, 0.3); // in case it goes to infinity BACKGROUND
    // return Color2(0.2, 0.4, 0.6); // in case it goes to infinity BACKGROUND
}

int main()
{
    int HEIGHT = 600;
    int WIDTH = 600;
    int maxBouncesOfRay = 15;
    MyVector eyeInitialPosition(0, -10, 0);
    MyVector LookAt(0, 0, 0);
    double distanceToMatrix = 2.5;
    MyVector verticalVector(1, 0, 0);
    int samplePerPixel = 40;
    Image image(WIDTH, HEIGHT, samplePerPixel);
    Eye eye(eyeInitialPosition, LookAt, distanceToMatrix, verticalVector, 0.003, WIDTH, HEIGHT);
    Torus t(MyVector(0, 0, 0), 1, 0.5, Color(220, 10, 10), 1);
    Sphere s({-2, 0, 0}, 1, Color(127, 250, 120), 0);
    Sphere s2({2, 0, 0}, 1, Color(127, 250, 120), 0.3);
    Plane p(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(100, 130, 140), 0);
    Parallelogram square(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(250, 127, 230), 0.6);
    Light l(MyVector(0, -5, -3), 2, Color(500, 500, 500));
    Light l2(MyVector(0, -5, 15), 5, Color(255, 255, 255));
    Light l3(MyVector(-15, -5, 0), 5, Color(255, 255, 255));
    Light l4(MyVector(0, -5, 3), 2, Color(500, 500, 500));
    const int sizeWorld = 8;
    Object *world[sizeWorld] = {&square, &t, &s, &s2, &l, &l2, &l3, &l4};
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            Color2 pixelColor(0, 0, 0);
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                Ray ray(&eye, pixel);
                pixelColor += PaintPixel(world, sizeWorld, &ray, maxBouncesOfRay);
            }
            pixelColor = ((double)1 / image.SamplesPerPixel) * pixelColor;

            image.matrix[i][j] = pixelColor.convertToColor();
            pixel = pixel + (eye.dimPixel * eye.horizontalVector);
        }
        pixel = eye.TopLeftPlain - (1 * (i + 1) * eye.dimPixel * eye.verticalVector);
    }
    image.printImage("prova");

    return 0;
}