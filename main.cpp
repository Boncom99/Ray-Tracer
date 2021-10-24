#include <iostream>
#define HEIGHT 500
#define WIDTH 500
#include "myVector.h"
#include "eye.h"
#include "object.h"
#include "ray.h"
#include "image.h"

using namespace std;

int main()
{
    MyVector eyeInitialPosition(0, 0, 1);
    MyVector eyeInitialDirection(1, 0, 0);
    double distanceToMatrix = 10;
    Image image(WIDTH, HEIGHT);
    Eye eye(eyeInitialPosition, eyeInitialDirection, distanceToMatrix);
    std::vector<int> color = {127, 127, 50};
    Sphere sphere({15, 0, 1}, 1, color);
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            MyVector dir = pixel + (eye.postion * (-1));
            Ray r(eye.postion, dir);
            if (intersection(r, sphere))
            {
                image.matrix[i][j] = sphere.color;
            }
            pixel.y -= eye.dimPixel;
        }
        pixel.y = eye.TopLeftPlain.y;
        pixel.z -= eye.dimPixel;
    }

    image.printImage("prova3");
    return 0;
}