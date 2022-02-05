#include "Ray.h"
Ray::Ray(MyVector pos, MyVector dir) : position(pos), direction(dir), bounces(0)
{
    direction.normalize();
}
Ray::Ray(Eye *eye, MyVector currentPixel) : bounces(0)
{
    position = eye->position;
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

void Ray::Rebound(MyVector normalVector, MyVector hitPosition)
{
    MyVector v = dotProduct(direction, normalVector) * normalVector;
    MyVector u = direction + (-1.0 * v);
    direction = (u - v);
    direction.normalize();
    position = hitPosition;
    bounces++;
}