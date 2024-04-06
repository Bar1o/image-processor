#include "image.h"

Image::Image() : width_(0), height_(0) {
}

Image::~Image() {
}

Image::Image(int width, int height) : width_(width), height_(height), pixels_(height_, std::vector(width_, RGB())) {
}

Image& Image::operator=(const Image& image) {
    width_ = image.width_;
    height_ = image.height_;
    pixels_ = image.pixels_;
    return *this;
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

RGB Image::GetRgb(int x, int y) const {
    y = std::max(std::min(y, height_ - 1), 0);
    x = std::max(std::min(x, width_ - 1), 0);
    return pixels_[y][x];
}

std::vector<std::vector<RGB>> Image::GetPixels() const {
    return pixels_;
}

void Image::SetPixels(std::vector<std::vector<RGB>> pixels) {
    pixels_ = pixels;
}

void Image::SetColor(RGB rgb, int x, int y) {
    if (x < 0 || y < 0 || x > width_ - 1 || y > height_ - 1) {
        return;
    }
    pixels_[y][x] = rgb;
}
