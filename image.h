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
    std::vector<std::vector<Color>> matrix;

public:
    Image();
    Image(int w, int h, int samples);
    int printImage(std::string name);
    void initializeImage();
    void MitjanaColors(int i, int j, std::vector<Color> c);
};

#endif