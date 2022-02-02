#define HEIGHT 500
#define WIDTH 500
#include "MyVector.h"
#include "Sphere.h"
#include "Eye.h"
#include "Ray.h"
#include "Image.h"

using namespace std;

void PaintImage(Sphere sphere[3], Eye eye, Image &image)
{
    int maxBounces = 10;
    MyVector pixel = eye.TopLeftPlain;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            vector<vector<int>> color(image.SamplesPerPixel, std::vector<int>(3, 0)); //guardem tots els colors de cada iteracio
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                double r2 = (double)rand() / RAND_MAX;
                double r3 = (double)rand() / RAND_MAX;
                MyVector randomPixel(pixel.x, pixel.y + r2 * eye.dimPixel, pixel.z + r3 * eye.dimPixel);
                MyVector dir = randomPixel + (eye.position * (-1));
                Ray ray(eye.position, dir);
                bool goesToInfinity = false;
                vector<int> pixelSampleColor(3, 0); //vector on guardem el color de cada pixel de cada sample
                while (ray.bounces < maxBounces && !goesToInfinity)
                {
                    goesToInfinity = true;
                    for (int s = 0; s < 3; s++) //per cada sphere
                    {
                        double t = sphere[s].hit(ray);
                        if (t != -1) //intersecció!
                        {
                            goesToInfinity = false;
                            MyVector auxPos = ray.getPosition(t);
                            ray.Rebound(sphere[s].NormalVector(auxPos), auxPos);
                            pixelSampleColor = sphere[s].color; //TODO estem agafant el color del ultim objecte amb el que rebota, quan hauriem de fer una barreja de tots
                            break;
                        }
                    }
                }
                color[sample] = pixelSampleColor;
            }

            image.MitjanaColors(i, j, color);
            pixel = pixel + (eye.dimPixel * eye.horizontalVector);
        }
        pixel = eye.TopLeftPlain - (1 * (i + 1) * eye.dimPixel * eye.verticalVector);
    }
}

int main()
{
    MyVector eyeInitialPosition(13, 15, 1);
    MyVector LookAt(0, 15, 1);
    double distanceToMatrix = 10;
    MyVector verticalVector(0, 0, 1);
    int samplePerPixel = 10;
    Image image(WIDTH, HEIGHT, samplePerPixel);
    Eye eye(eyeInitialPosition, LookAt, distanceToMatrix, verticalVector, 0.005);
    Sphere sphere2({-0.7, 15, 1}, 0.5, {0, 140, 0});
    Sphere sphere3({0, 15, 1}, 0.5, {0, 130, 0});
    Sphere sphere1({0.7, 15.5, 1}, 0.5, {127, 0, 0});
    Sphere s[3] = {sphere1, sphere2, sphere3};
    PaintImage(s, eye, image);
    image.printImage("prova3");

    return 0;
}