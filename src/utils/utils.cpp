#include "utils.hpp"

namespace minecraft {

void print_error(std::string text) {
    std::cerr << "[" GRAPHICS_BOLD COLOR_FOREGROUND_RED "ERROR" GRAPHICS_RESET "] " << text << "\n";
}

// https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
std::string slurp(const std::ifstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

}
