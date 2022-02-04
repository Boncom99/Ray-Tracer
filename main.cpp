#define HEIGHT 500
#define WIDTH 500
#include "MyVector.h"
#include "Sphere.h"
#include "Color.h"
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
            vector<Color> vecColor(image.SamplesPerPixel); // guardem tots els colors de cada iteracio
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                double r2 = (double)rand() / RAND_MAX;
                double r3 = (double)rand() / RAND_MAX;
                MyVector randomPixel(pixel.x, pixel.y + r2 * eye.dimPixel, pixel.z + r3 * eye.dimPixel);
                MyVector dir = randomPixel + (eye.position * (-1));
                Ray ray(eye.position, dir);
                bool goesToInfinity = false;
                vector<Color> pixelSampleColor(maxBounces); // vector on guardem el color de cada pixel de cada sample
                for (int bounce = 0; ray.bounces < maxBounces && !goesToInfinity; bounce++)
                // while (ray.bounces < maxBounces && !goesToInfinity)
                {
                    goesToInfinity = true;
                    for (int s = 0; s < 3; s++) // per cada sphere
                    {
                        double t = sphere[s].hit(ray);
                        if (t != -1) // intersecció!
                        {
                            goesToInfinity = false;
                            MyVector auxPos = ray.getPosition(t);
                            ray.Rebound(sphere[s].NormalVector(auxPos), auxPos);
                            Color c(sphere[s].color[0], sphere[s].color[1], sphere[s].color[2]);
                            // pixelSampleColor[bounce] = sphere[s].color; //TODO estem agafant el color del ultim objecte amb el que rebota, quan hauriem de fer una barreja de tots
                            pixelSampleColor[bounce] = c;
                            break;
                        }
                    }
                }
                vecColor[sample] = MitjanaColors2(pixelSampleColor, ray.bounces);
            }
            image.MitjanaColors(i, j, vecColor);
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