#ifndef _MINECRAFT_HPP_
#define _MINECRAFT_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

#include "utils/utils.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "blocks.hpp"

namespace minecraft {

class Minecraft {
    public:
    Minecraft();
    int initialise();
    void loop();


    private:
    Player player;
    GLFWwindow* window;
};

}

#endif
