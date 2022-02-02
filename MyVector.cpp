#include "MyVector.h"
MyVector::MyVector() : x(0), y(0), z(0)
{
}

MyVector::MyVector(double x, double y, double z) : x(x), y(y), z(z)
{
}
void MyVector::printVec()
{
    std::cout << "\n"
              << x << ", " << y << ", " << z << "\n";
}
MyVector operator*(const MyVector &v, double d)
{
    return MyVector(v.x * d, v.y * d, v.z * d);
}
MyVector operator*(double d, const MyVector &v)
{
    return MyVector(v.x * d, v.y * d, v.z * d);
}
MyVector operator+(const MyVector &v1, const MyVector &v2)
{
    return MyVector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
MyVector operator-(const MyVector &v1, const MyVector &v2)
{
    return MyVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
double MyVector::module()
{
    double aux = x * x + y * y + z * z;
    return sqrt(aux);
}
double MyVector::moduleSq()
{
    double aux = x * x + y * y + z * z;
    return aux;
}
void MyVector::normalize()
{
    double mod = this->module();
    x *= (1 / mod);
    y *= (1 / mod);
    z *= (1 / mod);
}

double dotProduct(MyVector v1, MyVector v2)
{
    double aux = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return aux;
}
MyVector crossProduct(MyVector v1, MyVector v2)
{
    double aux1 = v1.y * v2.z - v2.y * v1.z;
    double aux2 = v1.z * v2.x - v2.z * v1.x;
    double aux3 = v1.x * v2.y - v2.x * v1.y;
    return MyVector(aux1, (-1) * aux2, aux3);
}
void MyVector::absoluteValue()
{
    x = abs(x);
    y = abs(y);
    z = abs(z);
}