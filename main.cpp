#include "MyVector.h"
#include "Sphere.h"
#include "Color.h"
#include "Color2.h"
#include "Eye.h"
#include "Ray.h"
#include "Image.h"
#include "SphereSmooth.h"
#include "SphereRough.h"
#include "SphereGlass.h"
#include "Light.h"
#include <map>

using namespace std;

Color2 PaintPixel(Sphere **spheres, int size, Ray *ray, int Bounces)
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
        double t = spheres[s]->hit(ray);
        if (t != -1) // intersecció!
        {
            goesToInfinity = false;
            listObjects[spheres[s]] = t;
        }
    }
    if (!goesToInfinity)
    {
        auto object = min_element(listObjects.begin(), listObjects.end(), // escollim l'objecte amb que primer intersecciona amb el raig
                                  [](const auto &l, const auto &r)
                                  { return l.second < r.second; });
        MyVector auxPos = ray->getPosition(object->second);

        object->first->Rebound(ray, auxPos);
        Color2 c(0, 0, 0);
        c.convertToColor2(object->first->color);
        return (0.5 * c) * PaintPixel(spheres, size, ray, Bounces - 1);
    }
    return Color2(0.4, 0.4, 0.7); // in case it goes to infinity BACKGROUND
}

int main()
{
    int HEIGHT = 600;
    int WIDTH = 600;
    int maxBouncesOfRay = 15;
    MyVector eyeInitialPosition(0, 0, 1);
    MyVector LookAt(0, 15, 1);
    double distanceToMatrix = 10;
    MyVector verticalVector(1, 0, 0);
    int samplePerPixel = 20;
    Image image(WIDTH, HEIGHT, samplePerPixel);
    Eye eye(eyeInitialPosition, LookAt, distanceToMatrix, verticalVector, 0.004, WIDTH, HEIGHT);
    SphereGlass sphere5({-0.7, 13, 0.5}, 0.5, Color(255, 255, 255), 1.52);
    SphereRough sphere4({0, 14.5, 0}, 0.5, Color(0, 200, 200), 0.4);
    SphereSmooth sphere3({0, 15, 1}, 0.5, Color(0, 130, 0));
    SphereSmooth sphere2({-0.7, 15, 1}, 0.5, Color(0, 0, 140));
    SphereSmooth sphere1({0.7, 15.5, 1}, 0.5, Color(127, 0, 0));
    Sphere *s[5] = {&sphere1, &sphere2, &sphere3, &sphere4, &sphere5};
    Light light({-4, -1, 5}, 4, Color(255, 255, 255));
    // PaintImage(s, 5, &eye, &image, &light);
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            Color2 pixelColor(0, 0, 0);
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                Ray ray(&eye, pixel);
                pixelColor += PaintPixel(s, 5, &ray, maxBouncesOfRay);
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