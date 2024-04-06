#pragma once
#include <vector>
#include "RGB.h"

class Image {
private:
    int width_;
    int height_;
    std::vector<std::vector<RGB>> pixels_;

public:
    Image();
    Image(int width, int height);
    ~Image();
    Image& operator=(const Image& image);

    RGB GetRgb(int x, int y) const;
    void SetColor(RGB rgb, int x, int y);

    int GetWidth() const;
    int GetHeight() const;

    std::vector<std::vector<RGB>> GetPixels() const;
    void SetPixels(std::vector<std::vector<RGB>> pixels);

    friend void SaveFile(const char* path, Image& image);

    void Read(const char* path);
};