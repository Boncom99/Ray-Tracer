#ifndef QUATERNION_H
#define QUATERNION_H
#include <math.h>
#include <stdlib.h>
#include "MyVector.h"
#include <iostream>

class Quaternion
{
public:
    double x;
    double y;
    double z;
    double k;

public:
    Quaternion();
    Quaternion(MyVector a, double k);
    Quaternion(double x, double y, double z, double k);
    void printQuat();
    friend Quaternion operator*(double d, const Quaternion &v);
    friend Quaternion operator*(const Quaternion &v, double d);
    friend Quaternion operator+(const Quaternion &v1, const Quaternion &v2);
    friend Quaternion operator+(const Quaternion &v1, const double d);
    Quaternion &operator+=(const Quaternion &v2)
    {
        x += v2.x;
        y += v2.y;
        z += v2.z;
        k += v2.k;
        return *this;
    }
    Quaternion &operator+=(const double &d)
    {
        x += d;
        return *this;
    }
    Quaternion &operator*=(const double &d)
    {
        x *= d;
        y *= d;
        z *= d;
        k *= d;
        return *this;
    }
    friend Quaternion operator-(const Quaternion &v1, const Quaternion &v2);
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
        case 3:
            return k;
        }
        return 0;
    }
    double QModule();
    double QModuleSq();
    void QNormalize();
    void QAbsoluteValue();
};
Quaternion product(Quaternion v1, Quaternion v2);
Quaternion Qsq(Quaternion v1); // quadrat d' un quaternió (optimitzada)
Quaternion from3Dto4D(MyVector v, double d);
#endif
