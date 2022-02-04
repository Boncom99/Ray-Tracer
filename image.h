#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <iostream>
#include "Color.h"
#include <fstream>
#include <string>
class Image
{
public:
    int width;
    int height;
    int SamplesPerPixel;
    std::vector<std::vector<std::vector<int>>> matrix;

public:
    Image();
    Image(int w, int h, int samples);
    int printImage(std::string name);
    void initializeImage();
    void MitjanaColors(int i, int j, std::vector<Color> c);
};

#endif