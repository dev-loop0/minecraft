#include "utils.hpp"

namespace minecraft {

void print_error(std::string text) {
    std::cerr << "[" GRAPHICS_BOLD COLOR_FOREGROUND_RED "ERROR" GRAPHICS_RESET "] " << text << "\n";
}

std::string from_GL_error(int error) {
    switch(error) {
        case GL_NO_ERROR: return "NO_ERROR";
        case GL_INVALID_ENUM: return "INVALID_ENUM";
        case GL_INVALID_OPERATION: return "INVALID_OPERATION";
        case GL_STACK_OVERFLOW: return "STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW: return "STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY: return "OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
        default: return "UNKNOWN";
    }
}

// https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
std::string slurp(const std::ifstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

}
