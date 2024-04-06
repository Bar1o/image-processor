#pragma once
#include "filter.h"
#include "image.h"
#include "RGB.h"
#include <vector>
#include <cmath>

class GreyScale : public Filter {
public:
    explicit GreyScale(Image& image) : Filter(image){};
    ~GreyScale() = default;
    void Apply(Image& image) override;
};

class Negative : public Filter {
public:
    explicit Negative(Image& image) : Filter(image){};
    ~Negative() = default;
    void Apply(Image& image) override;
};

class Sharpening : public Filter {
public:
    explicit Sharpening(Image& image) : Filter(image){};
    ~Sharpening() = default;
    void Apply(Image& image) override;
};

class Edge : public Filter {
public:
    explicit Edge(float threshold);
    ~Edge() = default;
    void Apply(Image& image) override;

private:
    float threshold_ = 0;
};

class Crop : public Filter {
public:
    explicit Crop(int width, int height);
    ~Crop() = default;
    void Apply(Image& image) override;

private:
    int width_;
    int height_;
};

class ColorControls : public Filter {
    /*
    contrast + brightness
    идеально при contrast = 10, brightness = 0.5 => лена станет металлик
    (1, 20) => lena toxic
    */
public:
    ColorControls(float constrast, float brightness);
    ~ColorControls() = default;
    void Apply(Image& image) override;

private:
    float contrast_ = 1;
    float brightness_;
};

class GaussianBlur : public Filter {
public:
    explicit GaussianBlur(float sigma);
    ~GaussianBlur() = default;
    float DoGauss(float x);  // NOLINT
    void DoBlur(Image& image, int axis);
    void Apply(Image& image) override;

private:
    float pi_ = 3.14159265358979323846f;  // NOLINT
    float sigma_ = 1;
};
