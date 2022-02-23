#include "Image.h"
Image::Image() : width(0), height(0), matrix()
{
}

Image::Image(int w, int h, int samples) : width(w), height(h), SamplesPerPixel(samples)

{
    matrix.resize(height);
    for (size_t i = 0; i < height; ++i)
    {
        matrix[i].resize(width);
    }

    initializeImage();
}

int Image::printImage(std::string name)
{
    std::ofstream output;
    if (name == "")
    {
        std::time_t t = std::time(0);
        name = std::to_string(t);
    }
    output.open("Output/time_" + name + ".ppm", std::ios::out); // TODO canviar ppm (compresio) png

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
            // output << matrix[i][j].red << " " << matrix[i][j].green << " " << matrix[i][j].blue << " ";
            double r = matrix[i][j].red / SamplesPerPixel;
            double g = matrix[i][j].green / SamplesPerPixel;
            double b = matrix[i][j].blue / SamplesPerPixel;
            output << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' ' << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' ' << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << ' ';
        }
        output << "\n";
    }

    output.close();
    return 0;
}
void Image::initializeImage()
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            matrix[i][j] = Color(0, 0, 0);
        }
    }
}
