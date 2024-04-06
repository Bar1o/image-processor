#include <iostream>
#include "parser.h"
#include "open_save.h"
#include "all_filters.h"
#include <vector>
#include <string>
#include <stdexcept>

Parse::Parse(int argc, char** argv) {
    Image img;
    std::vector<float> args;
    // нужно написать обработку ошибок путей

    for (size_t i = 1; i < 2; ++i) {
        std::string arg = argv[i];
        if (arg.length() < 0 || arg.substr(arg.length() - 4) != ".bmp") {
            throw std::invalid_argument("invalid file format");
        }
    }

    this->open_path_ = argv[1];
    this->save_path_ = argv[2];
    img.Read(open_path_);
    SaveFile(save_path_, img);

    img.Read(save_path_);
    for (size_t i = 3; i < argc; ++i) {
        auto it = FILTERS.find(argv[i]);
        if (it != FILTERS.end()) {
            if (std::string(argv[i]) == "-edge" || std::string(argv[i]) == "-blur") {
                try {
                    float argument = 0;
                    if (i + 2 <= argc) {
                        argument = std::stof(argv[i + 1]);
                        if (argument < 0) {
                            throw std::runtime_error("argument must be positive");
                        }
                        it->second[0](img, args = {argument});
                    } else {
                        throw std::runtime_error("filter needs a number");
                    }
                } catch (...) {
                    throw std::runtime_error(std::string(argv[i]) + " filter needs a number");
                }
            } else if (std::string(argv[i]) == "-crop" || std::string(argv[i]) == "-ccont") {
                try {
                    if (i + 3 <= argc) {
                        float arg1 = std::stof(argv[i + 1]);
                        float arg2 = std::stof(argv[i + 2]);
                        if (arg1 < 0 || arg2 < 0) {
                            throw std::runtime_error("arguments must be positive");
                        }
                        it->second[0](img, args = {arg1, arg2});
                    }

                } catch (...) {
                    throw std::runtime_error("filter needs two numeric params");
                }
            } else {
                it->second[0](img, args = {});
            }
        } else if (argv[i][0] == '-') {
            throw std::runtime_error("unknown filter: " + std::string(argv[i]));
        }

        SaveFile(save_path_, img);
    }
}
