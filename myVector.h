#ifndef MYVECTOR_H
#define MYVECTOR_H
#endif

class MyVector
{
public:
    double x;
    double y;
    double z;

public:
    MyVector();
    MyVector(double x, double y, double z);
    void printVec();
    friend MyVector operator*(MyVector &v, double d);
    ~MyVector();
};

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
MyVector operator*(MyVector &v, double d)
{
    return MyVector(v.x * d, v.y * d, v.z * d);
}
MyVector::~MyVector()
{
}
