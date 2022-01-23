#include <iostream>
#define HEIGHT 500
#define WIDTH 500
#include "myVector.h"
#include "eye.h"
#include "object.h"
#include "ray.h"
#include "image.h"

using namespace std;
void PaintImage(Sphere sphere, Eye eye, Image &image)
{
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            MyVector dir = pixel + (eye.postion * (-1));
            Ray r(eye.postion, dir);
            if (r.intersection(sphere))
            {
                image.matrix[i][j] = sphere.color;
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
    Sphere sphere2({15, 2, 1}, 0.5, {200, 100, 20});
    Sphere s[2] = {sphere1, sphere2};
    for (int i = 0; i < 2; i++)
    {
        PaintImage(s[i], eye, image);
    }

    image.printImage("prova3");
    return 0;
}