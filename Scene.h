#ifndef SCENE_H
#define SCENE_H
#include "Object.h"
#include "MyVector.h"
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
    case 0:
        HEIGHT = 600;
        WIDTH = 600;
        maxBouncesOfRay = 15;
        eyePosition = MyVector(0, -10, 0);
        lookAt = MyVector(0, 0, 0);
        distanceToMatrix = 2.5;
        dimentionPixel = 0.003;
        verticalVector = MyVector(0, 0, 1);
        samplePerPixel = 40;
        background = Color(0, 0, 0);
        world.push_back(new Parallelogram(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(250, 127, 230), 0.6));
        world.push_back(new Torus(MyVector(0, 0, 0), 1, 0.5, Color(220, 10, 10), 1));
        world.push_back(new Sphere({-2, 0, 0}, 1, Color(127, 250, 120), 0));
        world.push_back(new Sphere({2, 0, 0}, 1, Color(127, 250, 120), 0.3));
        world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(100, 130, 140), 0));
        world.push_back(new Light(MyVector(0, -5, -3), 2, Color(255, 255, 255)));
        world.push_back(new Light(MyVector(0, -5, 15), 5, Color(255, 255, 255)));
        world.push_back(new Light(MyVector(-15, -5, 0), 5, Color(255, 255, 255)));
        world.push_back(new Light(MyVector(0, -5, 3), 2, Color(255, 255, 255)));
        size = world.size();
        break;
    case 1:
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
        world.push_back(new Parallelogram(MyVector(4, 1, 0), MyVector(0, 0, 1), MyVector(3, 2, 0.5), Color(250, 127, 230), 0.6));
        world.push_back(new Torus(MyVector(0, 0, 0), 1, 0.5, Color(220, 10, 10), 0.5));
        world.push_back(new Sphere({-2, 0, 1}, 1, Color(10, 250, 220), 0));
        world.push_back(new Sphere({2, 0, 1}, 1, Color(127, 250, 120), 0.1));
        world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(100, 130, 190), 0.3));
        world.push_back(new Light(MyVector(15, 10, 3), 7, Color(255, 255, 255)));
        world.push_back(new Light(MyVector(-10, 13, 3), 7, Color(255, 255, 255)));
        world.push_back(new Light(MyVector(-10, -10, 3), 7, Color(255, 255, 255)));
        size = world.size();

        break;
    case 2:
        HEIGHT = 600;
        WIDTH = 600;
        maxBouncesOfRay = 15;
        eyePosition = MyVector(0, 0, 3);
        lookAt = MyVector(0, 10, 0);
        distanceToMatrix = 1;
        dimentionPixel = 0.003;
        verticalVector = MyVector(0, 0.4, 1);
        samplePerPixel = 30;
        background = Color(0, 0, 0);
        world.push_back(new Sphere({0, 10, 1}, 1, Color(220, 220, 220), 0));
        world.push_back(new Sphere({3, 9, 1}, 1, Color(220, 220, 220), 0));
        world.push_back(new Sphere({0, 10, -100}, 100, Color(250, 250, 250), 1));
        world.push_back(new Light(MyVector(-20, -4, 3), 10, Color(4 * 255, 4 * 255, 4 * 255)));
        size = world.size();

        break;
    }
}

#endif