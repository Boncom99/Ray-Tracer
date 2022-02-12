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
    output.open("Output/" + name + ".ppm", std::ios::out);

    if (!output.is_open())
    {
        std::cout << "couldn't find the file " << name << "in the Output folder" << std::endl;
        return 0;
    }
    // header
    output << "P3 \n"
           << width << " " << height << "\n255 \n";
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            output << matrix[i][j].red << " " << matrix[i][j].green << " " << matrix[i][j].blue << " ";
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
void Image::MitjanaColors(int i, int j, std::vector<Color> c)
{
    int red = 0;
    int green = 0;
    int blue = 0;
    for (int i = 0; i < SamplesPerPixel; i++)
    {
        red += c[i].red;
        green += c[i].green;
        blue += c[i].blue;
    }

    matrix[i][j] = Color(red / SamplesPerPixel, green / SamplesPerPixel, blue / SamplesPerPixel);
}
