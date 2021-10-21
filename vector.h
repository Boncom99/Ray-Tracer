#ifndef VECTOR_H
#define VECTOR_H
#endif

class Vector
{
public:
    double x;
    double y;
    double z;

public:
    Vector();
    Vector(int x, int y, int z);
    void printVec();
    ~Vector();
};

Vector::Vector() : x(0), y(0), z(0)
{
}
Vector::Vector(int x, int y, int z) : x(x), y(y), z(z)
{
}
void Vector::printVec()
{
    std::cout << "\n"
              << x << ", " << y << ", " << z << "\n";
}
Vector::~Vector()
{
}
