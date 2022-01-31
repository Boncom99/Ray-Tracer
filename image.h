#ifndef IMAGE_H
#define IMAGE_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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
    void MitjanaColors(int i, int j, std::vector<std::vector<int>> c);
};

#endif