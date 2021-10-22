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

Eye::Eye(MyVector pos, MyVector dir, double distance) : postion(pos), direction(dir), distanceToMatrix(distance), dimPixel(0.005)
{
    direction.normalize();
    MyVector z(0, 0, 1);
    centerOfPlain = postion + (direction * distanceToMatrix);
    MyVector aux = crossProduct(direction, z);
    TopLeftPlain = centerOfPlain + (aux * (dimPixel * WIDTH / 2) + z * (dimPixel * HEIGHT / 2));
}
Eye::~Eye()
{
}

#endif