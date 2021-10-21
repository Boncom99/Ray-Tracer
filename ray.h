#ifndef Ray_H
#define Ray_H
class Ray
{
public:
    MyVector position;
    MyVector direction;
    double time;

public:
    Ray(MyVector pos, MyVector dir, double t);
    double intersection(Ray r, Object o);
    ~Ray();
};

Ray::Ray(MyVector pos, MyVector dir, double t) : position(pos), direction(dir), time(t)
{
}

double Ray::intersection(Ray r, Object o)
{
    //TODO
}
Ray::~Ray()
{
}

#endif