#include <iostream>
#include "myVector.h"
#include "eye.h"
#include "ray.h"
#include "image.h"
#include "object.h"
using namespace std;

int main()
{
    //MyVector v(1, 2, 3);
    //Ray r(1, 2, 3,1,2,3);
    MyVector initialPosition(0, 0, 0);
    MyVector initialDirection(1, 1, 0);
    double distanceToMatrix = 10;
    Image image(400, 400);
    Eye eye(initialPosition, initialDirection, distanceToMatrix);
    Sphere sphere({1, 1, 1}, 4);
    MyVector plain = eye.direction * distanceToMatrix;
    eye.direction.printVec();
    plain.printVec();

    image.printImage("prova2");
    return 0;
}