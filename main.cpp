#include "MainHeader.h"

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Scene scene(11);
    Image image(scene.WIDTH, scene.HEIGHT, scene.widthOfMatrix, scene.samplePerPixel, scene.gammaCorrection, scene.blur);
    Eye eye(scene.eyePosition, scene.lookAt, scene.distanceToMatrix, scene.verticalVector, image.dimPixel, scene.WIDTH, scene.HEIGHT);
    MyVector pixel = eye.TopLeftPlain;
    JuliaSet julia(0, Quaternion(-0.55, 0.2, 0, 0), Color(0.8, 0.6, 0.5));

    for (int i = 0; i < image.height; i++)
    {
        // pixel = eye.TopLeftPlain - (1 * (i + 1) * image.dimPixel * eye.verticalVector); // TODOO borrar
        for (int j = 0; j < image.width; j++)
        {
            // pixel = pixel + j * (image.dimPixel * eye.horizontalVector); // TODOOO borrar
            Color pixelColor(0, 0, 0);
            for (int sample = 0; sample < image.SamplesPerPixel; sample++)
            {
                Ray ray(&eye, pixel, image.blur);
                pixelColor += PaintPixel(scene, &ray, scene.maxBouncesOfRay);
            }
            image.matrix[i][j] = pixelColor;
            pixel = pixel + (image.dimPixel * eye.horizontalVector);
        }
        pixel = eye.TopLeftPlain - (1 * (i + 1) * image.dimPixel * eye.verticalVector);
        std::cerr << "\rScanlines remaining: " << image.height - i << ' ' << std::flush;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    int frameTimeS = static_cast<int>(diff.count());
    string name = "Time: " + std::to_string(frameTimeS) + ", Width: " + std::to_string(scene.WIDTH) + ", Height: " + std::to_string(scene.HEIGHT);
    image.printImage(name);
    std::cout << "total time: " << frameTimeS << "s" << std::endl;

    return 0;
}