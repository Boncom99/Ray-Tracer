#ifndef EYE_H
#define EYE_H
#include "MyVector.h"
class Eye
{
public:
    MyVector postion;
    MyVector direction;
    double distanceToMatrix;
    MyVector centerOfPlain;
    MyVector TopLeftPlain; //top left position of the matrix.
    double dimPixel;

public:
    Eye(MyVector pos, MyVector dir, double distance, double dimPixel);
};
Eye::Eye(MyVector pos, MyVector dir, double distance, double dimPixel) : postion(pos), direction(dir), distanceToMatrix(distance), dimPixel(dimPixel)
{
    direction.normalize();
    MyVector z(0, 0, 1);
    centerOfPlain = postion + (direction * distanceToMatrix);
    MyVector aux(crossProduct(direction, z));
    TopLeftPlain = centerOfPlain + (aux * (dimPixel * WIDTH / 2) + z * (dimPixel * HEIGHT / 2));
}

#endif