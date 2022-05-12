#include "Eye.h"
Eye::Eye(MyVector pos, MyVector LookAt, double distance, MyVector verticalVector, double dimPixel, int width, int height) : position(pos), LookAt(LookAt), distanceToMatrix(distance), verticalVector(verticalVector), dimPixel(dimPixel), width(width), height(height)
{
    direction = LookAt - position;
    direction.normalize();
    verticalVector.normalize();
    centerOfPlain = position + (direction * distanceToMatrix);
    horizontalVector = MyVector(crossProduct(direction, verticalVector));
    horizontalVector.absoluteValue();
    TopLeftPlain = centerOfPlain + ((-1 * horizontalVector) * (dimPixel * width / 2) + verticalVector * (dimPixel * height / 2));
    // TopLeftPlain.printVec();
    // centerOfPlain.printVec();
}
MyVector Eye::blur(float radius)
{
    if (radius != 0)
    {

        double randX = rand() % 100 - 50;
        double randY = rand() % 100 - 50;
        double randZ = rand() % 100 - 50;
        MyVector randomVector(randX, randY, randZ);
        randomVector.normalize();
        randomVector *= radius;
        return position + randomVector;
    }
    return position;
}