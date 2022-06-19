#include "MainHeader.h"
#include <thread>
void threadFunction(int start, int end, Scene scene, Eye eye, Image *image)
{
    for (int i = start; i < end; i++)
    {
        MyVector pixel = eye.TopLeftPlain - (i * image->dimPixel * eye.verticalVector);
        MainLoop(i, scene, eye, pixel, image);
    }
}
int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Scene scene(9);
    Image image(scene.WIDTH, scene.HEIGHT, scene.widthOfMatrix, scene.samplePerPixel, scene.gammaCorrection, scene.blur);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, image.dimPixel, scene.WIDTH, scene.HEIGHT);
    const int core = std::thread::hardware_concurrency();
    int m = scene.HEIGHT / core;
    std::vector<std::thread> threads;

    for (int i = 0; i < core; i++)
    {
        int end = m * i + m;
        if (i == core - 1)
            end = scene.HEIGHT;
        threads.push_back(std::thread(threadFunction, m * i, end, scene, eye, &image));
    }

    for (auto &th : threads)
    {
        th.join();
    }

     auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    int frameTimeS = static_cast<int>(diff.count());
    string name = "Time: " + std::to_string(frameTimeS) + ",  " + std::to_string(scene.WIDTH) + "x" + std::to_string(scene.HEIGHT);
    image.printImage(name);
    std::cout << "total time: " << frameTimeS << "s" << std::endl;

    return 0;
}