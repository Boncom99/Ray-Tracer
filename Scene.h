#ifndef SCENE_H
#define SCENE_H
#include "Object.h"
#include "MyVector.h"
#include <math.h>
#include <list>
class Scene
{
public:
    std::vector<Object *> world;
    int size;
    int HEIGHT;
    int WIDTH;
    int maxBouncesOfRay;
    MyVector eyePosition;
    MyVector lookAt;
    double distanceToMatrix;
    double dimentionPixel;
    MyVector verticalVector;
    int samplePerPixel;
    Color background;
    float lightAbsortion = 0.7;
    Scene(int i);
};

Scene::Scene(int i)
{
    switch (i)
    {
    default:
    case 0:
    {

        HEIGHT = 600;
        WIDTH = 600;
        maxBouncesOfRay = 15;
        eyePosition = MyVector(-1, -10, 3);
        lookAt = MyVector(0, 0, 0);
        verticalVector = MyVector(1, 10, 101 / 3);
        verticalVector.normalize();
        distanceToMatrix = 2.4;
        dimentionPixel = 0.003;
        samplePerPixel = 70;
        background = Color(0, 0, 0);
        // world.push_back(new Parallelogram(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(0.96, 0.5, 0.7), 0.6));
        world.push_back(new Torus(MyVector(0, 0, 0), 1, 0.5, Color(0.8, 0.1, 0.1), 0));
        double r = 13;
        world.push_back(new Sphere({0, 0, 0}, r + 2, Color(1, 1, 1), 0));
        // world.push_back(new Sphere({-2, 0, 0}, 1, Color(0.5, 0.76, 0.45), 0));
        // world.push_back(new Sphere({2, 0, 0}, 1, Color(0.5, 0.76, 0.45), 0.3));
        // world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(0.8, 0.8, 0.8), 1));
        double a = M_PI * 5 / 4;
        double c = M_PI * 7 / 4;
        double b = M_PI / 4;
        double d = M_PI / 5;
        world.push_back(new Light(MyVector(r * cos(a) * sin(b), r * sin(a) * sin(b), r * cos(b)), 2, Color(3, 3, 3)));
        world.push_back(new Light(MyVector(r * cos(c) * sin(d), r * sin(c) * sin(d), r * cos(d)), 2, Color(3, 3, 3)));
        // world.push_back(new Light(MyVector(0, -15, 2), 5, Color(4, 4, 4)));
        size = world.size();
        break;
    }
    case 1:
    {

        HEIGHT = 600;
        WIDTH = 600;
        maxBouncesOfRay = 15;
        eyePosition = MyVector(0, -10, 10);
        lookAt = MyVector(0, 0, 0);
        distanceToMatrix = 2;
        dimentionPixel = 0.003;
        verticalVector = MyVector(0, 1, 1);
        samplePerPixel = 30;
        background = Color(0, 0, 0);
        world.push_back(new Parallelogram(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(0.99, 0.5, 0.87), 0.6));
        world.push_back(new Torus(MyVector(0, 0, 0), 1, 0.5, Color(0.9, 0.1, 0.1), 0));
        world.push_back(new Sphere({-2, 0, 1}, 1, Color(0.1, 0.9, 0.9), 0));
        world.push_back(new Sphere({2, 0, 1}, 1, Color(0.5, 0.87, 0.45), 0));
        world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(0.3, 0.51, .55), 0.3));
        world.push_back(new Light(MyVector(-10, -10, 3), 7, Color(2, 2, 2)));
        size = world.size();

        break;
    }
    case 2:
    {

        HEIGHT = 800;
        WIDTH = 800;
        maxBouncesOfRay = 15;
        eyePosition = MyVector(0, -10, 5);
        lookAt = MyVector(0, 0, 0);
        verticalVector = MyVector(0, 0.5, 1);
        verticalVector.normalize();
        distanceToMatrix = 0.8;
        dimentionPixel = 0.001;
        samplePerPixel = 100;
        // background = Color(0.1, 0.2, 0.3);
        background = Color();
        world.push_back(new Sphere({0, 0, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({2, 2, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({0, 0, -100}, 100, Color(0.8, 0.8, 0.8), 1));
        world.push_back(new Light(MyVector(-20, 4, 15), 10, Color(4, 4, 4)));
        size = world.size();

        break;
    }
    }
}

#endif