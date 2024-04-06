#include "RGB.h"
#include <algorithm>

RGB::RGB() : r_(0), g_(0), b_(0) {
}

RGB::RGB(float r, float g, float b) : r_(r), g_(g), b_(b) {
}

RGB &RGB::operator=(const RGB &rgb) {
    r_ = rgb.r_;
    g_ = rgb.g_;
    b_ = rgb.b_;
    return *this;
}

RGB operator*(RGB rgb, int factor) {
    float f = static_cast<float>(factor);
    return RGB(rgb.r_ * f, rgb.g_ * f, rgb.b_ * f);
}

RGB operator+(RGB left, const RGB &right) {
    return RGB(left.r_ + right.r_, left.g_ + right.g_, left.b_ + right.b_);
}

RGB::~RGB() {
}
