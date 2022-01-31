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
    std::vector<std::vector<std::vector<int>>> matrix;

public:
    Image();
    Image(int w, int h);
    void addColor(int w, int h, std::vector<int> color);
    int printImage(std::string name);
    void initializeImage();
    ~Image();
};

#endif