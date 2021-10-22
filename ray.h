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
    bool intersection(Ray r, Sphere sphere);
    MyVector getPosition(double t);
    double distance(double t, Sphere sphere);
    ~Ray();
};

Ray::Ray(MyVector pos, MyVector dir, double t) : position(pos), direction(dir), time(t)
{
    direction.normalize();
}
MyVector Ray::getPosition(double t)
{
    MyVector aux = position + (direction * t);
    return aux;
}

double Ray::distance(double t, Sphere sphere)
{
    MyVector aux = getPosition(t) + (sphere.center * (-1));
    return aux.module() - sphere.radius;
}
bool Ray::intersection(Ray r, Sphere sphere)
{
    double t = 0;
    double d = 1;
    for (size_t i = 0; i < 100; i++)
    {
        d = r.distance(t, sphere);
        if (d == 0)
        {
            return 1;
        }
        t += d;
    }

    return 0;
}
Ray::~Ray()
{
}

#endif