#ifndef EYE_H
#define EYE_H
class Eye
{
public:
    MyVector postion;
    MyVector direction;
    double distanceToMatrix;
    MyVector centerOfPlain;
    MyVector TopLeftPlain;
    double dimPixel;

public:
    Eye(MyVector pos, MyVector dir, double distance);
    ~Eye();
};

Eye::Eye(MyVector pos, MyVector dir, double distance) : postion(pos), direction(dir), distanceToMatrix(distance)
{
    centerOfPlain = postion + (direction * distanceToMatrix);
}
Eye::~Eye()
{
}

#endif