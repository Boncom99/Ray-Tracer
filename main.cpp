#include "MyVector.h"
#include "Sphere.h"
#include "Color.h"
#include "Eye.h"
#include "Ray.h"
#include "Image.h"
#include "SphereSmooth.h"
#include "SphereRough.h"
#include "Light.h"
#include <map>

using namespace std;

void PaintImage(Sphere **sphere, int size, Eye *eye, Image *image, Light *light)
{
    int maxBounces = 15;
    MyVector pixel = eye->TopLeftPlain;

    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            vector<Color> vecColor(image->SamplesPerPixel); // guardem tots els colors de cada iteracio
            for (int sample = 0; sample < image->SamplesPerPixel; sample++)
            {
                map<Object *, double> listObjects;
                Ray ray(eye, pixel);
                bool goesToInfinity = false;
                vector<Color> pixelSampleColor(maxBounces); // vector on guardem el color de cada pixel de cada sample
                for (int bounce = 0; ray.bounces < maxBounces && !goesToInfinity; bounce++)
                {
                    goesToInfinity = true;
                    for (int s = 0; s < size; s++) // per cada sphere
                    {
                        double t = sphere[s]->hit(ray);
                        if (t != -1) // intersecció!
                        {
                            goesToInfinity = false;
                            listObjects[sphere[s]] = t;
                        }
                    }
                    if (!goesToInfinity)
                    {
                        auto object = min_element(listObjects.begin(), listObjects.end(), // escollim l'objecte amb que primer intersecciona amb el raig
                                                  [](const auto &l, const auto &r)
                                                  { return l.second < r.second; });
                        MyVector auxPos = ray.getPosition(object->second);

                        object->first->Rebound(&ray, auxPos);
                        pixelSampleColor[bounce] = object->first->color;
                    }
                }
                vecColor[sample] = MitjanaColors2(pixelSampleColor, ray.bounces);
            }
            image->MitjanaColors(i, j, vecColor);
            pixel = pixel + (eye->dimPixel * eye->horizontalVector);
        }
        pixel = eye->TopLeftPlain - (1 * (i + 1) * eye->dimPixel * eye->verticalVector);
    }
}

int main()
{
    int HEIGHT = 600;
    int WIDTH = 600;
    MyVector eyeInitialPosition(0, 0, 1);
    MyVector LookAt(0, 15, 1);
    double distanceToMatrix = 10;
    MyVector verticalVector(1, 0, 0);
    int samplePerPixel = 20;
    Image image(WIDTH, HEIGHT, samplePerPixel);
    Eye eye(eyeInitialPosition, LookAt, distanceToMatrix, verticalVector, 0.004, WIDTH, HEIGHT);
    SphereRough sphere4({0, 14.5, 0}, 0.5, Color(0, 200, 200), 0.4);
    SphereSmooth sphere3({0, 15, 1}, 0.5, Color(0, 130, 0));
    SphereSmooth sphere2({-0.7, 15, 1}, 0.5, Color(0, 0, 140));
    SphereSmooth sphere1({0.7, 15.5, 1}, 0.5, Color(127, 0, 0));
    Sphere *s[4] = {&sphere1, &sphere2, &sphere3, &sphere4};
    Light light({-4, -1, 5}, 4, Color(255, 255, 255));
    PaintImage(s, 4, &eye, &image, &light);
    image.printImage("prova");

    return 0;
}