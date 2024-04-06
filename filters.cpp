#include <algorithm>
#include <cmath>
#include "filters.h"
#include "image.h"
#include "RGB.h"

void GreyScale::Apply(Image& image) {

    for (int i = 0; i < image.GetWidth(); ++i) {
        for (int j = 0; j < image.GetHeight(); ++j) {
            RGB color = image.GetRgb(i, j);
            color.r_ = color.g_ = color.b_ = color.r_ * 0.299f + color.g_ * 0.587f + color.b_ * 0.114f;  // NOLINT
            image.SetColor(color, i, j);
        }
    }
}

void Negative::Apply(Image& image) {
    for (int i = 0; i < image.GetWidth(); ++i) {
        for (int j = 0; j < image.GetHeight(); ++j) {
            RGB color = image.GetRgb(i, j);
            color.r_ = 1 - color.r_;
            color.g_ = 1 - color.g_;
            color.b_ = 1 - color.b_;
            image.SetColor(color, i, j);
        }
    }
}

void Sharpening::Apply(Image& im) {
    Image new_im(im.GetWidth(), im.GetHeight());
    int factor = 5;  // NOLINT
    for (int i = 0; i < im.GetWidth(); ++i) {
        for (int j = 0; j < im.GetHeight(); ++j) {
            RGB color = im.GetRgb(i, j);
            color = (im.GetRgb(i - 1, j) + im.GetRgb(i + 1, j) + im.GetRgb(i, j + 1) + im.GetRgb(i, j - 1)) * (-1) +
                    im.GetRgb(i, j) * factor;

            color.r_ = std::min(1.0f, std::max(0.0f, color.r_));
            color.g_ = std::min(1.0f, std::max(0.0f, color.g_));
            color.b_ = std::min(1.0f, std::max(0.0f, color.b_));

            new_im.SetColor(color, i, j);
        }
    }
    im = new_im;
}
Edge::Edge(float threshold) {
    threshold_ = std::max(0.0f, std::min(threshold, 1.0f));
}

void Edge::Apply(Image& im) {
    int factor = 4;
    GreyScale gs(im);
    gs.Apply(im);
    Image new_im(im.GetWidth(), im.GetHeight());
    for (int i = 0; i < im.GetWidth(); ++i) {
        for (int j = 0; j < im.GetHeight(); ++j) {
            RGB color = im.GetRgb(i, j);
            color = (im.GetRgb(i - 1, j) + im.GetRgb(i + 1, j) + im.GetRgb(i, j + 1) + im.GetRgb(i, j - 1)) * (-1) +
                    im.GetRgb(i, j) * factor;
            if (color.r_ > threshold_) {
                new_im.SetColor(RGB{1, 1, 1}, i, j);
            } else {
                new_im.SetColor(RGB{0, 0, 0}, i, j);
            }
        }
    }
    im = new_im;
}

Crop::Crop(int width, int height) : width_(width), height_(height) {
}

void Crop::Apply(Image& im) {
    width_ = std::min(im.GetWidth(), width_);
    height_ = std::min(im.GetHeight(), height_);
    std::vector<std::vector<RGB>> pixels = im.GetPixels();
    std::reverse(pixels.begin(), pixels.end());

    for (int j = 0; j < height_; ++j) {
        pixels[j].resize(width_);
    }

    pixels.resize(height_);
    std::reverse(pixels.begin(), pixels.end());

    Image new_im(width_, height_);
    new_im.SetPixels(pixels);
    im = new_im;
}
ColorControls::ColorControls(float contrast, float brightness) {
    contrast_ = std::max(1.0f, contrast);
    brightness_ = std::max(0.0f, brightness);
}

void ColorControls::Apply(Image& im) {
    // был на сайте эппл из предложенных фильтров
    for (int i = 0; i < im.GetWidth(); ++i) {
        for (int j = 0; j < im.GetHeight(); ++j) {
            RGB color = im.GetRgb(i, j);
            RGB temp{0.5f, 0.5f, 0.5f};                          // NOLINT
            color = (color + (temp * (-1))) * contrast_ + temp;  // NOLINT
            color = color + RGB{brightness_, brightness_, brightness_};
            im.SetColor(color, i, j);
        }
    }
}

GaussianBlur::GaussianBlur(float sigma) {
    sigma_ = std::max(1.0f, sigma);
}

float GaussianBlur::DoGauss(float x) {                              // NOLINT
    float k1 = 1.0f / std::sqrt(2.0f * pi_ * sigma_ * sigma_);      // NOLINT
    return k1 * std::exp(-((x) * (x)) / (2.0f * sigma_ * sigma_));  // NOLINT
}

void GaussianBlur::DoBlur(Image& im, int axis) {

    Image new_im(im.GetWidth(), im.GetHeight());

    for (int i = 0; i < im.GetWidth(); ++i) {
        for (int j = 0; j < im.GetHeight(); ++j) {

            RGB color;

            for (int s = -static_cast<int>(std::ceil(3 * sigma_)); s < static_cast<int>(std::ceil(3 * sigma_)); ++s) {
                RGB pixel;
                if (axis == 1) {
                    pixel = im.GetRgb(i + s, j);
                } else {
                    pixel = im.GetRgb(i, j + s);
                }
                float ss = static_cast<float>(s);
                float coeff = DoGauss(ss);

                color.r_ += coeff * pixel.r_;
                color.g_ += coeff * pixel.g_;
                color.b_ += coeff * pixel.b_;
            }
            new_im.SetColor(color, i, j);
        }
    }
    im = new_im;
}

void GaussianBlur::Apply(Image& im) {
    DoBlur(im, 0);
    DoBlur(im, 1);
}
