#ifndef SCENE_H
#define SCENE_H
#include "Object.h"
#include <list>
class Scene
{
public:
    std::vector<Object *> world;
    int size;
    Scene(int i);
};

Scene::Scene(int i)
{
    switch (i)
    {
    case 0:
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
    }
}

#endif