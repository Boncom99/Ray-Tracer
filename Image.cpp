#include "Image.h"
#include <math.h>

Image::Image(int w, int h, float widthMatrix, int samples, float gammaCorrection, float blur) : width(w), height(h), widthMatrix(widthMatrix), SamplesPerPixel(samples), gammaCorrection(gammaCorrection), blur(blur)

{
    dimPixel = widthMatrix / width;
    matrix.resize(height);
    for (int i = 0; i < height; ++i)
    {
        matrix[i].resize(width);
    }

    initializeImage();
}

int Image::printImage(std::string name)
{
    std::ofstream output;
    std::time_t t = std::time(0);
    name = std::to_string((int)((t - 1645644194) / 100)) + name;
    output.open("Output/" + name + ".ppm", std::ios::out); // TODO canviar ppm (compresio) png

    if (!output.is_open())
    {
        std::cout << "couldn't find the file " << name << "in the Output folder" << std::endl;
        return 0;
    }
    // header
    output << "P3 \n"
           << width << " " << height << "\n255 \n";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // gamma correction of g=2
            double r = pow(matrix[i][j].red / SamplesPerPixel, gammaCorrection);
            double g = pow(matrix[i][j].green / SamplesPerPixel, gammaCorrection);
            double b = pow(matrix[i][j].blue / SamplesPerPixel, gammaCorrection);
            output << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' ' << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' ' << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << ' ';
        }
        output << "\n";
    }

    output.close();
    return 0;
}
void Image::initializeImage()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = Color(0, 0, 0);
        }
    }
}
