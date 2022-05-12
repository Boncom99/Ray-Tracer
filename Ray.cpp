#include "Ray.h"
Ray::Ray(MyVector pos, MyVector dir) : position(pos), direction(dir)
{
    direction.normalize();
}
Ray::Ray(Eye *eye, MyVector currentPixel, float blur)
{
    position = eye->blur(blur);
    double randV = (double)rand() / RAND_MAX;
    double randH = (double)rand() / RAND_MAX;
    MyVector randomPixel = currentPixel + eye->dimPixel * (randH * eye->horizontalVector + randV * eye->verticalVector);
    direction = randomPixel + (position * (-1));
    direction.normalize();
}
MyVector Ray::getPosition(double t)
{
    MyVector aux = position + (direction * t);
    return aux;
}
