#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

// very limited ANSI escape code support

#define ESCAPE "\x1b"
#define CSI ESCAPE "["

#define GRAPHICS_RESET CSI "0m"
#define GRAPHICS_BOLD CSI "1m"
#define GRAPHICS_FAINT CSI "2m"
#define GRAPHICS_ITALICS CSI "3m"
#define GRAPHICS_UNDERLINE CSI "4m"
#define GRAPHICS_SLOW_BLINK CSI "5m"
#define GRAPHICS_FAST_BLINK CSI "6m"
#define GRAPHICS_INVERT CSI "7m"
#define GRAPHICS_CONCEAL CSI "8m"
#define GRAPHICS_STRIKETHROUGH CSI "9m"
// TODO: fill them all in
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

#define COLOR_FOREGROUND_BLACK CSI "30m"
#define COLOR_FOREGROUND_RED CSI "31m"
#define COLOR_FOREGROUND_GREEN CSI "32m"
#define COLOR_FOREGROUND_YELLOW CSI "33m"
#define COLOR_FOREGROUND_BLUE CSI "34m"
#define COLOR_FOREGROUND_MAGENTA CSI "35m"
#define COLOR_FOREGROUND_CYAN CSI "36m"
#define COLOR_FOREGROUND_WHITE CSI "37m"

#define COLOR_BACKGROUND_BLACK CSI "40m"
#define COLOR_BACKGROUND_RED CSI "41m"
#define COLOR_BACKGROUND_GREEN CSI "42m"
#define COLOR_BACKGROUND_YELLOW CSI "43m"
#define COLOR_BACKGROUND_BLUE CSI "44m"
#define COLOR_BACKGROUND_MAGENTA CSI "45m"
#define COLOR_BACKGROUND_CYAN CSI "46m"
#define COLOR_BACKGROUND_WHITE CSI "47m"

namespace minecraft {

void print_error(std::string text);
std::string from_GL_error(int error);

std::string slurp(const std::ifstream& in);

}

#endif
