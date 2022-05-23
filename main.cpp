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
            if (child)
                child->Rebound(ray, impactPos);
            else
                object->first->Rebound(ray, impactPos);

            return (scene.lightAbsortion * object->first->color) * PaintPixel(scene, ray, Bounces - 1);
            return Color(0, 0, 0);
        }
        else
        {
            return object->first->color;
        }
    }
    return scene.background;
}
Color PaintFractal(Ray *ray, JuliaSet julia)
{
    Color clear(0.44, 0.33, 0.23);
    clear = 1.7 * clear;
    Color dark(0.44, 0.33, 0.23);
    dark = 0.3 * dark;
    Color DarkminusClear = dark + (-1.0 * clear); // resta dels colors
    double m = 600;                               // max number of iterations possible of hit function
    double count = julia.hit(ray);
    if (count < 0) // intersecció!
    {
        return Color(0, 0, 0);
    }
    // la funció que, per 0 iteracions ens retorna Clear, i per m interacions ens retorna Dark
    Color c = (-1.0 / (m * m) * count * count * DarkminusClear) + (2.0 / m * count * DarkminusClear) + clear;
    if (c.red <= dark.red)
        return dark;
    return c;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Scene scene(9);
    Image image(scene.WIDTH, scene.HEIGHT, scene.widthOfMatrix, scene.samplePerPixel, scene.gammaCorrection, scene.blur);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, image.dimPixel, scene.WIDTH, scene.HEIGHT);
    int max = 100;
    for (double Frame = 0; Frame < max; Frame++)
    {
        double angle0 = -1 * M_PI / 4;
        double angle1 = -1 * 3 * M_PI / 4;
        double angle = (double)(Frame * angle1 + (max - Frame) * angle0) / (double)max;

        eye.position = MyVector(4.0 * cos(angle), 4.0 * sin(angle), (double)Frame / max - 0.5);
        MyVector pixel = eye.TopLeftPlain;
        JuliaSet julia(0, Quaternion((double)(-1.5 * Frame + (max - Frame)) / (double)max, 0.4 * sin((double)Frame / 10.0), 0.1, 0));
        for (int i = 0; i < image.height; i++)
        {
            for (int j = 0; j < image.width; j++)
            {
                Color pixelColor(0, 0, 0);
                for (int sample = 0; sample < image.SamplesPerPixel; sample++)
                {
                    Ray ray(&eye, pixel, image.blur);
                    pixelColor += PaintFractal(&ray, julia);
                    // pixelColor += PaintPixel(scene, &ray, scene.maxBouncesOfRay);
                }
                image.matrix[i][j] = pixelColor;
                pixel = pixel + (image.dimPixel * eye.horizontalVector);
            }
            pixel = eye.TopLeftPlain - (1 * (i + 1) * image.dimPixel * eye.verticalVector);
            std::cerr << "\rScanlines remaining: " << image.height - i << ' ' << std::flush;
        }
        string name = std::to_string((int)Frame);
        // string name =  "Time: " + std::to_string(frameTimeS) + ", Width: " + std::to_string(scene.WIDTH) + ", Height: " + std::to_string(scene.HEIGHT);
        image.printImage(name);
        std::cout << "\n frame: "
                  << Frame << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    int frameTimeS = static_cast<int>(diff.count());
    std::cout << "total time: " << frameTimeS << "s" << std::endl;
    // cout << "Time To process image: " << frameTimeMs << "s" << endl;

    return 0;
}