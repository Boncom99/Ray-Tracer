#include "MyVector.h"
#include "Sphere.h"
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
#include <map>
#include <chrono>
using namespace std;

Color PaintPixel(Scene scene, Ray *ray, int Bounces)
{
    if (Bounces <= 0)
    {
        return Color(0, 0, 0);
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
        MyVector impactPos = ray->getPosition(object->second);
        if (dynamic_cast<Light *>(object->first) == nullptr) // en cas que impacti amb la font d'iluminació
        {

            SphereGlass *child = dynamic_cast<SphereGlass *>(object->first);
            // JuliaSet *julia = dynamic_cast<JuliaSet *>(object->first);
            if (child)
                child->Rebound(ray, impactPos);
            // else if (julia)
            {
                MyVector N = object->first->NormalVector(impactPos);
                return object->first->Phong(MyVector(-1, 5, -0.3), scene.eyePosition, impactPos, N);
            }
            object->first->Rebound(ray, impactPos);
            return (scene.lightAbsortion * object->first->color) * PaintPixel(scene, ray, Bounces - 1);
        }
        else
            return object->first->color;
    }
    return scene.background;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Scene scene(9);
    Image image(scene.WIDTH, scene.HEIGHT, scene.widthOfMatrix, scene.samplePerPixel, scene.gammaCorrection, scene.blur);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, image.dimPixel, scene.WIDTH, scene.HEIGHT);
    MyVector pixel = eye.TopLeftPlain;
    JuliaSet julia(0, Quaternion(-0.55, 0.2, 0, 0), Color(0.8, 0.6, 0.5));

    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            Color pixelColor(0, 0, 0);
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                Ray ray(&eye, pixel, image.blur);
                pixelColor += PaintPixel(scene, &ray, scene.maxBouncesOfRay);
            }
            image.matrix[i][j] = pixelColor;
            pixel = pixel + (image.dimPixel * eye.horizontalVector);
        }
        pixel = eye.TopLeftPlain - (1 * (i + 1) * image.dimPixel * eye.verticalVector);
        std::cerr << "\rScanlines remaining: " << image.height - i << ' ' << std::flush;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    int frameTimeS = static_cast<int>(diff.count());
    string name = "Time: " + std::to_string(frameTimeS) + ", Width: " + std::to_string(scene.WIDTH) + ", Height: " + std::to_string(scene.HEIGHT);
    image.printImage(name);
    std::cout << "total time: " << frameTimeS << "s" << std::endl;

    return 0;
}