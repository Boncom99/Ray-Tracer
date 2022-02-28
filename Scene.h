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
    float widthOfMatrix = 0.8;
    int maxBouncesOfRay;
    MyVector eyePosition;
    MyVector lookAt;
    double distanceToMatrix;
    double dimentionPixel;
    MyVector verticalVector;
    int samplePerPixel;
    Color background;
    float lightAbsortion = 0.6;
    float gammaCorrection = 1 / 2.5;
    Scene(int i);
};

Scene::Scene(int i)
{
    switch (i)
    {
    default:
    case 0:
    {

        HEIGHT = 800;
        WIDTH = 800;
        maxBouncesOfRay = 15;
        double r = 13;
        double cm = 1.9;
        eyePosition = MyVector(0, -1 * cm, cm);
        lookAt = MyVector(0, 0, 0);
        verticalVector = MyVector(0, cm, cm);
        verticalVector.normalize();
        distanceToMatrix = 0.5;
        dimentionPixel = 0.002;
        samplePerPixel = 60;
        background = Color(0, 0, 0);
        // world.push_back(new Parallelogram(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(0.96, 0.5, 0.7), 0.6));
        world.push_back(new Torus(MyVector(0, 0, 0), 1, 0.5, MyVector(0, 1, 0), Color(0.4, 1.55, 1.6), 1));
        world.push_back(new Sphere({0, 0, r - 1.5}, r, Color(1, 1, 1), 0));
        // world.push_back(new Sphere({-2, 0, 0}, 1, Color(0.5, 0.76, 0.45), 0));
        // world.push_back(new Sphere({2, 0, 0}, 1, Color(0.5, 0.76, 0.45), 0.3));
        // world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(0.8, 0.8, 0.8), 1));
        double a = M_PI * 5 / 4;
        double b = M_PI / 4;
        world.push_back(new Light(MyVector(r * cos(a) * sin(b), r * sin(a) * sin(b), r * cos(b) + r - 1.5), 2, Color(2.3, 2.3, 2.3)));
        // world.push_back(new Light(MyVector(r * cos(c) * sin(d), r * sin(c) * sin(d), r * cos(d)), 2, Color(2.3, 2.3, 2.5)));
        //  world.push_back(new Light(MyVector(0, -15, 2), 5, Color(4, 4, 4)));
        size = world.size();
        break;
    }
    case 1:
    {

        HEIGHT = 800;
        WIDTH = 800;
        maxBouncesOfRay = 20;
        eyePosition = MyVector(0, -10, 10);
        lookAt = MyVector(0, 0, 0);
        distanceToMatrix = 2;
        dimentionPixel = 0.002;
        verticalVector = MyVector(0, 1, 1);
        samplePerPixel = 50;
        background = Color(0, 0, 0);
        world.push_back(new Parallelogram(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(0.99, 0.5, 0.87), 0.6));
        world.push_back(new Torus(MyVector(0, 0, 0), 1, 0.5, MyVector(0, 1, 0), Color(1.4, 0.2, 0.2), 0));
        world.push_back(new Sphere({-2, 0, 1}, 1, Color(0.1, 0.9, 0.9), 0));
        world.push_back(new Sphere({2, 0, 1}, 1, Color(0.5, 0.87, 0.45), 0));
        world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(0.3, 0.51, .55), 0.3));
        world.push_back(new Light(MyVector(-10, -10, 3), 7, Color(2, 2, 2)));
        size = world.size();

        break;
    }
    case 2:
    {

        HEIGHT = 1600;
        WIDTH = 1600;
        widthOfMatrix = 0.8;
        maxBouncesOfRay = 50;
        eyePosition = MyVector(0, -10, 5);
        lookAt = MyVector(0, 0, 0);
        verticalVector = MyVector(0, 0.5, 1);
        verticalVector.normalize();
        distanceToMatrix = 0.8;
        dimentionPixel = widthOfMatrix / WIDTH;
        samplePerPixel = 250;
        background = Color(0.05, 0.1, 0.15);
        // background = Color();
        lightAbsortion = 0.7;
        gammaCorrection = 1 / 2.4;
        world.push_back(new Sphere({0, 0, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new SphereGlass({-1, -2, 1}, 1, Color(1, 1, 1), 1.52));
        world.push_back(new Torus(MyVector(-3, 0, 1), 1, 0.5, MyVector(0, 1, -1), Color(1.6, 0.4, 1.6), 1));
        world.push_back(new Torus(MyVector(3, -1, 1), 0.8, 0.35, MyVector(0, 1, 0), Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({2, 2, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({0, 0, -200}, 200, Color(0.4, 1.55, 1.6), 1));
        world.push_back(new Light(MyVector(-20, 4, 15), 10, Color(4, 4, 4)));
        size = world.size();

        break;
    }
    case 3:
    {
        // Cornell Box
        HEIGHT = 800;
        WIDTH = 800;
        widthOfMatrix = 2;
        maxBouncesOfRay = 50;
        eyePosition = MyVector(0, -5, 2);
        lookAt = MyVector(0, 0, 2);
        verticalVector = MyVector(0, 0, 1);
        verticalVector.normalize();
        distanceToMatrix = 2.4;
        dimentionPixel = widthOfMatrix / WIDTH;
        samplePerPixel = 100;
        background = Color(0.01, 0.01, 0.01);
        // background = Color();
        lightAbsortion = 0.9;
        gammaCorrection = 1 / 2.4;

        // side walls
        world.push_back(new Parallelogram(MyVector(0, 0, 4), MyVector(0, 4, 0), MyVector(-2, 0, 0), Color(1, 0.3, 0.3), 1));
        world.push_back(new Parallelogram(MyVector(0, 0, 4), MyVector(0, 4, 0), MyVector(2, 0, 0), Color(0.3, 1, 0.3), 1));
        // back wall
        world.push_back(new Parallelogram(MyVector(0, 0, 4), MyVector(4, 0, 0), MyVector(-2, 4, 0), Color(1, 1, 1), 1));
        // floor
        world.push_back(new Parallelogram(MyVector(4, 0, 0), MyVector(0, 4, 0), MyVector(-2, 0, 0), Color(1, 1, 1), 1));
        // roof
        world.push_back(new Parallelogram(MyVector(4, 0, 0), MyVector(0, 4, 0), MyVector(-2, 0, 4), Color(1, 1, 1), 1));
        // objects
        world.push_back(new Sphere({1, 3, 0.8}, 0.8, Color(0.7, 0.7, 0.7), 0));
        // world.push_back(new SphereGlass({-1, 2, 2.8}, 0.7, Color(0.7, 0.7, 0.7), 1.52));
        //   square
        world.push_back(new Parallelogram(MyVector(1, 1, 0), MyVector(0, 0, 2), MyVector(-1, 2.5, 0), Color(0.3, 0.3, 0.8), 1));
        world.push_back(new Parallelogram(MyVector(-1, 1, 0), MyVector(0, 0, 2), MyVector(-1, 2.5, 0), Color(0.3, 0.3, 0.8), 1));
        // world.push_back(new Parallelogram(MyVector(-1, 1, 0), MyVector(1, 1, 0), MyVector(-1, 2.5, 2), Color(0.3, 0.3, 0.8), 1));
        //  world.push_back(new Parallelogram(MyVector(-1, 1, 0), MyVector(0, 0, 2), MyVector(-3, 2.5, 0), Color(0.3, 0.3, 0.3), 1));

        // Light
        // world.push_back(new Light(MyVector(0, -9, 2), 1, Color(4, 4, 4)));
        world.push_back(new Light(MyVector(0, 2, 4.2), 0.5, Color(5, 5, 5)));

        // world.push_back(new Torus(MyVector(-3, 0, 1), 1, 0.5, MyVector(0, 1, -1), Color(1.6, 0.4, 1.6), 1));
        // world.push_back(new Torus(MyVector(3, -1, 1), 0.8, 0.35, MyVector(0, 1, 0), Color(0.7, 0.7, 0.7), 0));
        size = world.size();

        break;
    }
    }
}

#endif