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
#include "Scene.h"
#include <map>

using namespace std;

Color2 PaintPixel(Scene scene, Ray *ray, int Bounces)
{
    if (Bounces <= 0)
    {
        return Color2(0, 0, 0);
    }
    bool goesToInfinity = true;
    // Check if ray hits any object
    map<Object *, double> listObjects;   // list where we keep all objects that intersects with ray
    for (int s = 0; s < scene.size; s++) // per cada spheres
    {
        double t = scene.world[s]->hit(ray);
        if (t > 0.0001) // intersecció!
        {
            goesToInfinity = false;
            listObjects[scene.world[s]] = t;
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
            return (scene.lightAbsortion * convertToColor2(object->first->color)) * PaintPixel(scene, ray, Bounces - 1);
        }
        else
        {
            return convertToColor2(object->first->color);
        }
    }
    return scene.background;
}

int main()
{
    Scene scene(2);
    Image image(scene.WIDTH, scene.HEIGHT, scene.samplePerPixel);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, scene.dimentionPixel, scene.WIDTH, scene.HEIGHT);

    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            Color2 pixelColor(0, 0, 0);
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                Ray ray(&eye, pixel);
                pixelColor += PaintPixel(scene, &ray, scene.maxBouncesOfRay);
            }
            pixelColor = ((double)1 / image.SamplesPerPixel) * pixelColor;

            image.matrix[i][j] = pixelColor.convertToColor();
            pixel = pixel + (eye.dimPixel * eye.horizontalVector);
        }
        pixel = eye.TopLeftPlain - (1 * (i + 1) * eye.dimPixel * eye.verticalVector);
    }
    image.printImage("");

    return 0;
}