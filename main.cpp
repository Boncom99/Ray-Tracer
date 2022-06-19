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
double minPositiveTime(double array[], int n)
{
    int aux = -1;
    double val = 1000;
    for (int i = 0; i < n; i++)
    {
        if (array[i] < val && array[i] > 0)
        {
            val = array[i];
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
    double listTimes[3];
    // vector<double> listTimes(scene.size, 0);
    //  map<Object *, double> listObjects;   // list where we keep all objects that intersects with ray
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
        // double min = *min_element(listTimes.begin(), listTimes.end());
        double min = minPositiveTime(listTimes, scene.size);
        // double min = std::min_element(std::begin(listTimes), std::end(listTimes));
        Object *object;
        object = scene.world[min];

        MyVector impactPos = ray->getPosition(min);
        if (dynamic_cast<Light *>(object) == nullptr) // en cas que impacti amb la font d'iluminació
        {

            SphereGlass *child = dynamic_cast<SphereGlass *>(object);
            if (child)
                child->Rebound(ray, impactPos);

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

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Scene scene(10);
    Image image(scene.WIDTH, scene.HEIGHT, scene.widthOfMatrix, scene.samplePerPixel, scene.gammaCorrection, scene.blur);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, image.dimPixel, scene.WIDTH, scene.HEIGHT);
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < image.height; i++)
    {
        // pixel = eye.TopLeftPlain - (1 * (i + 1) * image.dimPixel * eye.verticalVector); // TODOO borrar
        for (int j = 0; j < image.width; j++)
        {
            //    pixel = pixel + j * (image.dimPixel * eye.horizontalVector); // TODOOO borrar
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