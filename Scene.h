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
    float blur = 1;
    int maxBouncesOfRay;
    MyVector eyePosition;
    MyVector lookAt;
    double distanceToMatrix;
    float dimentionPixel;
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
    // donut dins d'esfera :
    case 0:
    {

        HEIGHT = 400;
        WIDTH = 400;
        maxBouncesOfRay = 15;
        double r = 13;
        double cm = 1.9;
        eyePosition = MyVector(0, -1 * cm, cm);
        lookAt = MyVector(0, 0, 0);
        verticalVector = MyVector(0, cm, cm);
        verticalVector.normalize();
        distanceToMatrix = 0.5;
        widthOfMatrix=0.8;
        samplePerPixel = 60;
        blur=0;
        gammaCorrection=1;
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
        //dos esferes 
        HEIGHT = 400;
        WIDTH = 400;
        widthOfMatrix = 3;
        maxBouncesOfRay = 15;
        eyePosition = MyVector(2,-3,2);
        lookAt = MyVector(0, 2, 1);
        verticalVector = MyVector(0, 0, 1);
        distanceToMatrix = 2;
        samplePerPixel = 40;
        background = Color(0.6, 0.6, 0.65);
        lightAbsortion = 0.8;
        blur=0;
        gammaCorrection = 1/3 ;
        world.push_back(new Sphere({0, 1, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({2, 3, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({0, 0, -200}, 200, Color(0.6, 0.6, 0.5), 1));
        world.push_back(new Light(MyVector(-20, -2, 8), 7, Color(1, 1, 1)));
        size = world.size();

        break;
    }
    case 2:
    {
        //muli objectes
        HEIGHT = 500;
        WIDTH = 500;
        widthOfMatrix = 0.8;
        maxBouncesOfRay = 20;
        eyePosition = MyVector(0, -10, 5);
        lookAt = MyVector(0, 0, 0);
        verticalVector = MyVector(0, 0.5, 1);
        verticalVector.normalize();
        distanceToMatrix = 0.8;
        samplePerPixel = 50;
        background = Color(0.05, 0.1, 0.3);
        // background = Color();
        lightAbsortion = 0.7;
        blur=0;
        gammaCorrection = 1 / 2.4;
        world.push_back(new Sphere({0, 0, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new SphereGlass({-1, -2, 1}, 1, Color(1, 1, 1), 1.52));
        world.push_back(new Torus(MyVector(-3, 0, 1), 1, 0.5, MyVector(0, 1, -1), Color(1.6, 0.4, 1.6), 1));
        world.push_back(new Torus(MyVector(3, -1, 1), 0.8, 0.35, MyVector(0, 1, 0), Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({2, 2, 1}, 1, Color(0.7, 0.7, 0.7), 0));
        world.push_back(new Sphere({0, 0, -200}, 200, Color(0.4, 1.6, 1.6), 1));
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
    default:
    case 4:
    {
        // saturn
        HEIGHT = 1000;
        WIDTH = 1000;
        maxBouncesOfRay = 5;
        eyePosition = MyVector(0, 0, 0);
        lookAt = MyVector(0, 1, 0);
        verticalVector = MyVector(0, 0, 1);
        blur = 0.01;
        // verticalVector.normalize();
        distanceToMatrix = 10;
        widthOfMatrix = 3.5;
        dimentionPixel = widthOfMatrix / WIDTH;
        // dimentionPixel = 0.002;
        samplePerPixel = 150;
        background = Color(0, 0, 0);
        lightAbsortion = 0.9;
        gammaCorrection = 1 / 2.4;
        double R = 40;
        world.push_back(new Sphere({0.5, 10, 0.4}, 0.15, Color(0.7, 0.7, 0.7), 1));
        world.push_back(new Light({-R + 4, R, 0}, R, Color(0.85, 0.85, 0.7)));
        world.push_back(new Parallelogram(MyVector(1, 1, 0.02), MyVector(20, 0, 0), MyVector(-4, 6, 0), Color(0.1, 0.1, 0.1), 1));
        world.push_back(new Parallelogram(MyVector(1, 1, 0.2), MyVector(10, 0, 0), MyVector(4, R + 10, -1), Color(0.1, 0.1, 0.1), 1));
        // world.push_back(new Sphere({-2, 0, 0}, 1, Color(0.5, 0.76, 0.45), 0));
        // world.push_back(new Sphere({2, 0, 0}, 1, Color(0.5, 0.76, 0.45), 0.3));
        // world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -2), Color(0.8, 0.8, 0.8), 1));
        // world.push_back(new Light(MyVector(r * cos(c) * sin(d), r * sin(c) * sin(d), r * cos(d)), 2, Color(2.3, 2.3, 2.5)));
        //  world.push_back(new Light(MyVector(0, -15, 2), 5, Color(4, 4, 4)));
        size = world.size();
        break;
    }
    case 5:
    {
        // moon
        HEIGHT = 1200;
        WIDTH = 800;
        maxBouncesOfRay = 3;
        eyePosition = MyVector(0, 0, 0);
        lookAt = MyVector(0.4, 10, 0);
        verticalVector = MyVector(0, 0, 1);
        blur = 0;
        // verticalVector.normalize();
        distanceToMatrix = 6.2;
        widthOfMatrix = 3.5;
        // dimentionPixel = widthOfMatrix / WIDTH;
        samplePerPixel = 300;
        background = Color(0, 0, 0);
        lightAbsortion = 0.99;
        gammaCorrection = 1 / 2.6;
        world.push_back(new Sphere({1, 8, 1.5}, 0.5, Color(0.7, 0.7, 0.7), 1));
        world.push_back(new Light({14, 15, 1}, 7, Color(3, 3, 3)));
        size = world.size();
        break;
    }
case 6:
    {
        //profunditat de camp 
        HEIGHT = 600;
        WIDTH = 900;
        maxBouncesOfRay = 30;
        eyePosition = MyVector(2.1,-4 , 1);
        lookAt = MyVector(0, 20, -3);
        verticalVector = MyVector(0, 0, 1);
        blur = 0;
        distanceToMatrix = 7;
        widthOfMatrix = 4;
        samplePerPixel = 300;
        background = Color(0.15, 0.15, 0.25);
        lightAbsortion = 0.9;
        gammaCorrection = 1 / 2.6;
        world.push_back(new Light({13, 0, 6}, 5, Color(2.5, 2, 2)));
        for (int i = 1; i < 10; i++)
        {
        world.push_back(new Sphere({0, (double)(3*i), 0}, 0.8, Color(0.4, 1.4, 1.4), 0));
        }
        world.push_back(new Plane(MyVector(0, 0, 1), MyVector(0, 0, -0.8), Color(0.7, 0.6, 0.7), 0));
        
        size = world.size();
        break;
    }
case 7:
    {
        // exemple suabitat superficies
        HEIGHT = 200;
        WIDTH = 200;
        maxBouncesOfRay = 3;
        eyePosition = MyVector(0,-11,0);
        lookAt = MyVector(1, 2, 0);
        verticalVector = MyVector(0, 0, 1);
        blur = 0;
        distanceToMatrix = 12;
        widthOfMatrix = 13;
        samplePerPixel = 1;
        background = Color(1, 1,1);
        lightAbsortion = 0.9;
        gammaCorrection = 1 / 1;
        world.push_back(new Sphere({1, 1, 0}, 1, Color(0.1, 0.7, 0.1), 0));
        
        size = world.size();
        break;
    }
    }
}

#endif