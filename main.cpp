#include <iostream>
#include "ray.h"
#include "image.h"
#include "eye.h"
using namespace std;

int main()
{
    //MyVector v(1, 2, 3);
    //Ray r(1, 2, 3,1,2,3);
    MyVector initialPosition(0, 0, 0);
    MyVector initialDirection(0, 0, 0);
    int distanceToMatrix = 10;
    Image image(400, 400);
    Eye eye(initialPosition, initialDirection, distanceToMatrix);

    image.printImage("prova2");
    return 0;
}