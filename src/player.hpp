#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

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

namespace minecraft {

const int window_width = 1280, window_height = 720;

class Player {
    public:
    Player();

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);
    void set_yaw(float yaw);
    void set_pitch(float pitch);

    float get_x();
    float get_y();
    float get_z();
    float get_yaw();
    float get_pitch();

    void handle_inputs(GLFWwindow* window);
    void handle_mouse(GLFWwindow* window, double x, double y);

    Eigen::Matrix4f generate_view_matrix();

    private:
    float x, y, z;
    // yaw is left-right, pitch is up-down
    float yaw, pitch;
};

}

#endif
