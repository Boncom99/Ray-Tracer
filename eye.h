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
    MyVector TopLeftPlain; //top left position of the matrix.
    MyVector horizontalVector;
    MyVector verticalVector;
    double dimPixel;

public:
    Eye(MyVector pos, MyVector LookAt, double distance, MyVector verticalVector, double dimPixel);
};
Eye::Eye(MyVector pos, MyVector LookAt, double distance, MyVector verticalVector, double dimPixel) : position(pos), LookAt(LookAt), distanceToMatrix(distance), verticalVector(verticalVector), dimPixel(dimPixel)
{
    direction = LookAt - position;
    direction.normalize();
    verticalVector.normalize();
    centerOfPlain = position + (direction * distanceToMatrix);
    horizontalVector = MyVector(crossProduct(direction, verticalVector));
    horizontalVector.absoluteValue();
    TopLeftPlain = centerOfPlain + ((-1 * horizontalVector) * (dimPixel * WIDTH / 2) + verticalVector * (dimPixel * HEIGHT / 2));
    TopLeftPlain.printVec();
    centerOfPlain.printVec();
}

#endif