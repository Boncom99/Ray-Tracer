#ifndef IMAGE_H
#define IMAGE_H
#include <fstream>
#include <string>
#include <vector>
class Image
{
public:
    int width;
    int height;
    std::vector<std::vector<std::vector<int>>> matrix;

public:
    Image();
    Image(int w, int h);
    int printImage(std::string name);
    void initializeImage();
    ~Image();
};

Image::Image() : width(0), height(0), matrix()
{
}

Image::Image(int w, int h) : width(w), height(h)
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
Image::~Image()
{
}

#endif