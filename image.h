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
    int SamplesPerPixel;
    float gammaCorrection;
    std::vector<std::vector<Color>> matrix;

public:
    Image(int w, int h, int samples, float gammaCorrection);
    int printImage(std::string name);
    void initializeImage();
};

#endif