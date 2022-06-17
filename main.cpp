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

using namespace std;

Color PaintPixel(Scene scene, Ray *ray, int Bounces)
{
    if (Bounces <= 0)
    {
        return Color(0, 0, 0);
    }
    bool goesToInfinity = true;
    // Check if ray hits any object
    double listObjects[scene.size];
    // map<Object *, double> listObjects;   // list where we keep all objects that intersects with ray
    for (int s = 0; s < scene.size; s++) // per cada spheres
    {
        double t = scene.world[s]->hit(ray);
        if (t > 0.0001) // intersecció!
        {
            goesToInfinity = false;
            // listObjects[scene.world[s]] = t;
            listObjects[s] = t;
        }
    }
    if (!goesToInfinity)
    {
        double *min = std::min_element(listObjects, listObjects + scene.size);
        Object *object;
        object = scene.world[*min];

        MyVector impactPos = ray->getPosition(*min);
        if (dynamic_cast<Light *>(object) == nullptr) // en cas que impacti amb la font d'iluminació
        {

            SphereGlass *child = dynamic_cast<SphereGlass *>(object);
            if (child)
                child->Rebound(ray, impactPos);
            else
                object->Rebound(ray, impactPos);

            return (scene.lightAbsortion * object->color) * PaintPixel(scene, ray, Bounces - 1);
            return Color(0, 0, 0);
        }
        else
        {
            return object->color;
        }
    }
    return scene.background;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Scene scene(10);
    Image image(scene.WIDTH, scene.HEIGHT, scene.widthOfMatrix, scene.samplePerPixel, scene.gammaCorrection, scene.blur);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, image.dimPixel, scene.WIDTH, scene.HEIGHT);
    MyVector pixel = eye.TopLeftPlain;
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
    // cout << "Time To process image: " << frameTimeMs << "s" << endl;
    return 0;
}