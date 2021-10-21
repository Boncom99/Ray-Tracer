#ifndef EYE_H
#define EYE_H
class Eye
{
public:
    MyVector postion;
    MyVector direction;
    double distanceToMatrix;
    MyVector TopLeft;
    double dimPixel;

public:
    Eye();
    Eye(MyVector pos, MyVector dir, double distance);
    ~Eye();
};

Eye::Eye()
{
}

Eye::Eye(MyVector pos, MyVector dir, double distance) : postion(pos), direction(dir), distanceToMatrix(distance)
{
}
Eye::~Eye()
{
}

#endif