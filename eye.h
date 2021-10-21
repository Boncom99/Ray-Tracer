#ifndef EYE_H
#define EYE_H
#include "myVector.h"
class Eye
{
public:
    MyVector postion;
    MyVector direction;
    distanceToMatrix;
    MyVector TopLeft;
    double dimPixel;

public:
    Eye();
    Eye(MyVector pos, MyVector dir, int distance);
    ~Eye();
};

Eye::Eye()
{
}

Eye::Eye(MyVector pos, MyVector dir, int distance) : postion(pos), direction(dir), distanceToMatrix(distance)
{
}
Eye::~Eye()
{
}

#endif