#include <iostream>
#include "myVector.h"
#include "eye.h"
#include "object.h"
#include "ray.h"
#include "image.h"
using namespace std;

int main()
{
    //MyVector v(1, 2, 3);
    //Ray r(1, 2, 3,1,2,3);
    MyVector eyeInitialPosition(3, 3, 3);
    MyVector eyeInitialDirection(1, 1, 0);
    double distanceToMatrix = 10;
    Image image(400, 400);
    Eye eye(eyeInitialPosition, eyeInitialDirection, distanceToMatrix);
    Sphere sphere({1, 1, 1}, 4);
    MyVector centerOfPlain = eye.postion + (eye.direction * distanceToMatrix);
    eye.direction.printVec();
    eye.postion.printVec();
    std::cout << eye.distanceToMatrix << endl;
    centerOfPlain.printVec();

    image.printImage("prova2");
    return 0;
}