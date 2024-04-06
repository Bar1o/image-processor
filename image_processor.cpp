#include <iostream>
#include <stdexcept>
#include "parser.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "HELP"
                     "{имя программы} {путь к входному файлу} {путь к выходному файлу} "
                     "[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...] [-{имя фильтра 2} [параметр "
                     "фильтра 1] [параметр фильтра 2] ...] ..."
                     "Filters available: \n"
                     "-crop width height, -gs, -neg, -sharp, -edge threshold, -blur sigma"
                  << std::endl;
    } else if (argc < 3) {
        throw std::runtime_error("Not enough arguments");
        return 0;
    } else {
        try {
            Parse(argc, argv);
        } catch (std::runtime_error& e) {
            throw e;
            std::cerr << "unexpected error" << std::endl;
            return -1;
        }
    }
    /*
    1) parse the command line arguments
    2) apply filters to the image
    3) save the image
    */
    return 0;
}
