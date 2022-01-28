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

            MyVector dir = pixel + (eye.postion * (-1));
            Ray ray(eye.postion, dir);
            bool goesToInfinity = false;
            while (ray.bounces < maxBounces && !goesToInfinity)
            {
                goesToInfinity = true;
                for (int s = 0; s < 3; s++)
                {
                    double t = sphere[s].hit(ray);
                    if (t != -1) //intersecció!
                    {
                        goesToInfinity = false;
                        MyVector auxPos = ray.getPosition(t);
                        ray.Rebound(sphere[s].NormalVector(auxPos), auxPos);
                        image.matrix[i][j] = sphere[s].color;
                        break;
                    }
                }
            }
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
    Image image(WIDTH, HEIGHT);
    Eye eye(eyeInitialPosition, eyeInitialDirection, distanceToMatrix);
    std::vector<int> color = {127, 127, 50};
    Sphere sphere1({15, -1, 1}, 1, color);
    Sphere sphere2({15, 0, 1}, 0.5, {200, 100, 20});
    Sphere sphere3({15, 01, 1}, 0.5, {255, 1, 2});
    Sphere s[3] = {sphere1, sphere2, sphere3};
    PaintImage(s, eye, image);

    image.printImage("prova3");
    return 0;
}