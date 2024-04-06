#pragma once
#include "image.h"

class Filter {
public:
    Filter() = default;
    explicit Filter(Image& image) : image_(&image){};
    ~Filter() = default;
    virtual void Apply(Image& image) = 0;

protected:
    Image* image_;
};
