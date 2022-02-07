#ifndef SQUARE_H
#define SQUARE_H
#include "MyVector.h"
#include "Object.h"
#include "Ray.h"
class Square : public Object
{
public:
    MyVector point1;
    MyVector point2;
    double height;
    Square();
    Square(MyVector point1, MyVector point2, double height);
    MyVector NormalVector(MyVector position);
    double hit(Ray ray);
};

Square::Square() : point1(MyVector()), point2(MyVector()), height(0)
{
}
Square::Square(MyVector point1, MyVector point2, double height) : point1(point1), point2(point2), height(height)
{
}
#endif
