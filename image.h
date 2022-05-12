#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <iostream>
#include "Color.h"
#include <fstream>
#include <string>
#include <ctime>
class Image
{
public:
    int width;
    int height;
    float widthMatrix;
    int SamplesPerPixel;
    float gammaCorrection;
    float blur;
    float dimPixel;
    std::vector<std::vector<Color>> matrix;

public:
    Image(int w, int h, float widthMatrix, int samples, float gammaCorrection, float blur);
    int printImage(std::string name);
    void initializeImage();
};

#endif