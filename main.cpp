#include <iostream>
#define HEIGHT 500
#define WIDTH 500
#include "myVector.h"
#include "eye.h"
#include "object.h"
#include "ray.h"
#include "image.h"

using namespace std;
void PaintImage(Sphere sphere[2], Eye eye, Image &image)
{
    int maxBounces = 5;
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            MyVector dir = pixel + (eye.postion * (-1));
            Ray r(eye.postion, dir);
            bool goesToInfinity = false;
            while (r.bounces < maxBounces && !goesToInfinity)
            {
                goesToInfinity = true;
                for (int s = 0; s < 2; s++)
                {
                    double t = r.intersection(sphere[s]);
                    if (t != -1) //intersecció!
                    {
                        goesToInfinity = false;
                        MyVector auxPos = r.getPosition(t);
                        r.direction = sphere->Rebound(r.position, r.direction);
                        r.position = auxPos;
                        image.matrix[i][j] = sphere[s].color;
                        r.bounces++;
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
    Sphere sphere2({15, 0.5, 1}, 0.5, {200, 100, 20});
    Sphere s[2] = {sphere1, sphere2};
    PaintImage(s, eye, image);

    image.printImage("prova3");
    return 0;
}