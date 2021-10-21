#ifndef OBJECT_H
#define OBJECT_H
class Object
{
public:
    MyVector color;

public:
    Object(/* args */);
    ~Object();
};

Object::Object(/* args */)
{
}

Object::~Object()
{
}
class Sphere : public Object
{
public:
    MyVector center;
    double radius;

public:
    Sphere(/* args */);
    Sphere(MyVector cent, double rad);
    ~Sphere();
};

Sphere::Sphere(/* args */) : radius(0)
{
}

Sphere::Sphere(MyVector cent, double rad) : center(cent), radius(rad)
{
}
Sphere::~Sphere()
{
}

#endif