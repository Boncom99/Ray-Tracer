#define HEIGHT 500
#define WIDTH 500
#include "MyVector.h"
#include "Sphere.h"
#include "Eye.h"
#include "Ray.h"
#include "Image.h"

using namespace std;
void PaintImage(Sphere sphere[3], Eye eye, Image &image)
{
    int maxBounces = 5;
    int SamplesPerPixel = 20;
    MyVector pixel = eye.TopLeftPlain;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            for (int sample = 0; sample < SamplesPerPixel; sample++)
            {
                double r2 = (double)rand() / RAND_MAX;
                double r3 = (double)rand() / RAND_MAX;
                MyVector randomPixel(pixel.x, pixel.y + r2 * eye.dimPixel, pixel.z + r3 * eye.dimPixel);
                MyVector dir = randomPixel + (eye.postion * (-1));
                Ray ray(eye.postion, dir);
                bool goesToInfinity = false;
                while (ray.bounces < maxBounces && !goesToInfinity)
                {
                    goesToInfinity = true;
                    for (int s = 0; s < 3; s++) //per cada sphere
                    {
                        double t = sphere[s].hit(ray);
                        if (t != -1) //intersecció!
                        {
                            goesToInfinity = false;
                            MyVector auxPos = ray.getPosition(t);
                            ray.Rebound(sphere[s].NormalVector(auxPos), auxPos);
                            image.addColor(i, j, sphere[s].color);
                            break;
                        }
                    }
                }
            }
            pixel.y -= eye.dimPixel;
        }
        pixel.y = eye.TopLeftPlain.y;
        pixel.z -= eye.dimPixel;
    }
}
void Prova(Sphere sphere[3], Eye eye, Image &image)
{
    int maxBounces = 10;
    MyVector pixel(1, 0, 1);
    double r2 = (double)rand() / RAND_MAX;
    cout << r2 << "   ";
    double r3 = (double)rand() / RAND_MAX;
    MyVector randomPixel(pixel.x, pixel.y + r2, pixel.z + r3);
    MyVector dir = pixel + (eye.postion * (-1));
    Ray ray(eye.postion, dir);
    cout << "ray direction:";
    ray.direction.printVec();
    cout << "\n";
    bool goesToInfinity = false;
    while (ray.bounces < maxBounces && !goesToInfinity)
    {
        goesToInfinity = true;

        cout << "start again \n";
        cout << "bounces:" << ray.bounces << "\n";
        for (int s = 0; s < 3; s++)
        {
            cout << "sphere : " << s << "\n";
            double t = sphere[s].hit(ray);
            cout << "t= " << t << " \n";

            if (t != -1) //intersecció!
            {
                cout << "impact\n";
                goesToInfinity = false;
                MyVector auxPos = ray.getPosition(t);
                ray.Rebound(sphere[s].NormalVector(auxPos), auxPos);
                cout << "ray direction:";
                ray.direction.printVec();
                cout << "ray position:";
                ray.position.printVec();
                break;
            }
        }
    }
}
int main()
{
    MyVector eyeInitialPosition(0, 0, 1);
    MyVector eyeInitialDirection(1, 0, 0);
    double distanceToMatrix = 10;
    Image image(WIDTH, HEIGHT);
    Eye eye(eyeInitialPosition, eyeInitialDirection, distanceToMatrix, 0.005);
    std::vector<int> color = {127, 127, 50};
    Sphere sphere2({13, 0, 1}, 0.5, {200, 100, 20});
    Sphere sphere3({15, 1, 1}, 0.5, {255, 1, 2});
    Sphere sphere1({11, 1.2, 1}, 0.5, color);
    Sphere s[3] = {sphere1, sphere2, sphere3};
    PaintImage(s, eye, image);
    //Prova(s, eye, image);

    image.printImage("prova3");
    return 0;
}