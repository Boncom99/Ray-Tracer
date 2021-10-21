#include <iostream>
#include "ray.h"
using namespace std;

int main()
{
    Vector v(1, 2, 3);
    cout << v.x << v.y << v.z;
    Ray r(1, 2, 3);
    r.direction.printVec();
    return 0;
}