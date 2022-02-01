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
        for (size_t j = 0; j < width; j++)
        {
            matrix[i][j].resize(3);
        }
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
    //header
    output << "P3 \n"
           << width << " " << height << "\n255 \n";
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            output << matrix[i][j][0] << " " << matrix[i][j][1] << " " << matrix[i][j][2] << " ";
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
            matrix[i][j][0] = 0;
            matrix[i][j][1] = 0;
            matrix[i][j][1] = 0;
        }
    }
}
void Image::MitjanaColors(int i, int j, std::vector<std::vector<int>> c)
{
    std::vector<int> Color(3, 0);
    int R = 0;
    int G = 0;
    int B = 0;
    for (int s = 0; s < SamplesPerPixel; s++)
    {
        R += c[s][0];
        G += c[s][1];
        B += c[s][2];
    }
    Color[0] = R / SamplesPerPixel;
    Color[1] = G / SamplesPerPixel;
    Color[2] = B / SamplesPerPixel;
    matrix[i][j] = Color;
}
