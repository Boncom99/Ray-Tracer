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
    int maxBounces = 5;
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
                MyVector dir = randomPixel + (eye.postion * (-1));
                Ray ray(eye.postion, dir);
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
            pixel.y -= eye.dimPixel;
        }
        pixel.y = eye.TopLeftPlain.y;
        pixel.z -= eye.dimPixel;
    }
}

int main()
{
    MyVector eyeInitialPosition(0, 0, 1);
    MyVector eyeInitialDirection(1, 0, 0);
    double distanceToMatrix = 10;
    Image image(WIDTH, HEIGHT, 100);
    Eye eye(eyeInitialPosition, eyeInitialDirection, distanceToMatrix, 0.005);
    std::vector<int> color = {127, 127, 50};
    Sphere sphere2({13, 0, 1}, 0.5, {200, 100, 20});
    Sphere sphere3({15, 1, 1}, 0.5, {255, 1, 2});
    Sphere sphere1({11, 1.2, 1}, 0.5, color);
    Sphere s[3] = {sphere1, sphere2, sphere3};
    PaintImage(s, eye, image);
    image.printImage("prova3");
    return 0;
}