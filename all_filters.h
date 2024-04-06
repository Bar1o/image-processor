#pragma once
#include <map>
#include <functional>
#include <string>
#include "filter.h"
#include "filters.h"
#include "image.h"
#include "parser.h"
#include <vector>

using FilterFunction = std::function<void(Image&, std::vector<float>)>;
using FilterTable = std::map<std::string, std::vector<FilterFunction>>;

const FilterTable FILTERS = {{"-gs", {[](Image& image, std::vector<float> args = {}) {
                                  GreyScale gs(image);
                                  gs.Apply(image);
                              }}},
                             {"-neg", {[](Image& image, std::vector<float> args = {}) {
                                  Negative neg(image);
                                  neg.Apply(image);
                              }}},
                             {"-sharp", {[](Image& image, std::vector<float> args = {}) {
                                  Sharpening sh(image);
                                  sh.Apply(image);
                              }}},
                             {"-edge", {[](Image& image, std::vector<float> args = {}) {
                                  Edge sh(args[0]);
                                  sh.Apply(image);
                              }}},
                             {"-crop", {[](Image& image, std::vector<float> args = {}) {
                                  int width = static_cast<int>(args[0]);
                                  int height = static_cast<int>(args[1]);
                                  Crop cr(width, height);
                                  cr.Apply(image);
                              }}},
                             {"-ccont", {[](Image& image, std::vector<float> args = {}) {
                                  ColorControls cc(args[0], args[1]);
                                  cc.Apply(image);
                              }}},
                             {"-blur", {[](Image& image, std::vector<float> args = {}) {
                                  GaussianBlur blur(args[0]);
                                  blur.Apply(image);
                              }}}};
