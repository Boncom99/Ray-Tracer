#ifndef SUBTRACTIONN_H
#define SUBTRACTIONN_H

class Subtraction : public Object
{
public:
    Object *object1;
    Object *object2;

public:
    Subtraction(Object *o1, Object *o2, double r);
    MyVector NormalVector(MyVector position);
    double hit(Ray *ray);
    void Rebound(Ray *ray, MyVector hitPosition);
    double distance(MyVector p);
};

#endif