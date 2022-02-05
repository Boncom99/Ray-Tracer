#ifndef EYE_H
#define EYE_H
#include "MyVector.h"
class Eye
{
public:
    MyVector position;
    MyVector LookAt;
    MyVector direction;
    double distanceToMatrix;
    MyVector centerOfPlain;
    MyVector TopLeftPlain; // top left position of the matrix.
    MyVector horizontalVector;
    MyVector verticalVector;
    double dimPixel;
    int width;
    int height;

public:
    Eye(MyVector pos, MyVector LookAt, double distance, MyVector verticalVector, double dimPixel, int width, int height);
};

#endif