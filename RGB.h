#pragma once

struct RGB {
    float r_ = 0;
    float g_ = 0;
    float b_ = 0;

    RGB();
    RGB(float r, float g, float b);
    ~RGB();
    RGB& operator=(const RGB& rgb);

    friend RGB operator*(RGB rgb, int factor);
    friend RGB operator+(RGB left, const RGB& right);
};
