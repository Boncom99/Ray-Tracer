#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <math.h>
#include <stdlib.h>
#include <iostream>

class MyVector
{
public:
    double x;
    double y;
    double z;

public:
    MyVector();
    // MyVector(const MyVector &p); //copy contructor
    MyVector(double x, double y, double z);
    void printVec();
    friend MyVector operator*(double d, const MyVector &v);
    friend MyVector operator*(const MyVector &v, double d);
    friend MyVector operator+(const MyVector &v1, const MyVector &v2);
    MyVector &operator+=(const MyVector &v2)
    {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        return *this;
    }
    MyVector &operator*=(const double &d)
    {
        x *= d;
        y *= d;
        z *= d;
        return *this;
    }
    friend MyVector operator-(const MyVector &v1, const MyVector &v2);
    double operator[](int i) const
    {
        switch (i)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
        return 0;
    }
    double module();
    double moduleSq();
    void normalize();
    void absoluteValue();
    // double dotProduct(MyVector v1, MyVector v2);
    // MyVector crossProduct(MyVector v1, MyVector v2);
};
double dotProduct(MyVector v1, MyVector v2);
MyVector crossProduct(MyVector v1, MyVector v2);
#endif
