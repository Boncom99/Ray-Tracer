#include "Quaternion.h"
Quaternion::Quaternion() : x(0), y(0), z(0), k(0)
{
}

Quaternion::Quaternion(double x, double y, double z, double k) : x(x), y(y), z(z), k(k)
{
}
void Quaternion::printQuat()
{
    std::cout << "\n"
              << x << ", " << y << ", " << z << ", " << k << "\n";
}
Quaternion operator*(const Quaternion &v, double d)
{
    return Quaternion(v.x * d, v.y * d, v.z * d, v.k * d);
}
Quaternion operator*(double d, const Quaternion &v)
{
    return Quaternion(v.x * d, v.y * d, v.z * d, v.k * d);
}
Quaternion operator+(const Quaternion &v1, const Quaternion &v2)
{
    return Quaternion(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.k + v2.k);
}
Quaternion operator+(const Quaternion &v1, const double d)
{
    return Quaternion(v1.x + d, v1.y, v1.z, v1.k);
}
Quaternion operator-(const Quaternion &v1, const Quaternion &v2)
{
    return Quaternion(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.k - v2.k);
}
double Quaternion::QModule()
{
    double aux = x * x + y * y + z * z + k * k;
    return sqrt(aux);
}
double Quaternion::QModuleSq()
{
    double aux = x * x + y * y + z * z + k * k;
    return aux;
}
void Quaternion::QNormalize()
{
    double mod = this->QModule();
    x *= (1 / mod);
    y *= (1 / mod);
    z *= (1 / mod);
    k *= (1 / mod);
}

Quaternion product(Quaternion a, Quaternion b)
{
    double aux1 = (a.x * b.x - a.y * b.y - a.z * b.z - a.k * b.k);
    double aux2 = (a.x * b.y + a.y * b.x + a.z * b.k - a.k * b.z);
    double aux3 = (a.x * b.z - a.y * b.k + a.z * b.x + a.k * b.y);
    double aux4 = (a.x * b.k + a.y * b.z - a.z * b.y + a.k * b.x);
    return Quaternion(aux1, aux2, aux3, aux4);
}
void Quaternion::QAbsoluteValue()
{
    x = abs(x);
    y = abs(y);
    z = abs(z);
    k = abs(k);
}

Quaternion from3Dto4D(MyVector v, double d)
{
    return Quaternion(v.x, v.y, v.z, d);
}