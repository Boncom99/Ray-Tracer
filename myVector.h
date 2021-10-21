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
    MyVector(int x, int y, int z);
    void printVec();
    ~MyVector();
};

MyVector::MyVector() : x(0), y(0), z(0)
{
}
MyVector::MyVector(int x, int y, int z) : x(x), y(y), z(z)
{
}
void MyVector::printVec()
{
    std::cout << "\n"
              << x << ", " << y << ", " << z << "\n";
}
MyVector::~MyVector()
{
}
