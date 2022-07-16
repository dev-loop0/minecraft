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

void error_callback(int error, const char* msg){
    minecraft::print_error(std::string("OpenGL error ") + std::to_string(error) + ": " + msg);
}

int main(int argc, char** argv){
    if(glfwInit() != GL_TRUE){
        std::cerr << "GLFW initialisation failed.\n";
        return 1;
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // I mean Minecraft already uses OpenGL but whatever
    GLFWwindow* window = glfwCreateWindow(minecraft::window_width, minecraft::window_height, "Minecraft: OpenGL (tm) version", nullptr, nullptr);
    if(!window){
        std::cerr << "The window creation failed. Perhaps you do not have the correct version of GLFW?\n";
        std::cerr << "Expected 3.3, got " << glfwGetVersionString() << "\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return 1;
    }

    minecraft::Shader vertex(GL_VERTEX_SHADER, minecraft::slurp(std::ifstream("assets/shaders/main.vsh")));
    vertex.compile();
    if(vertex.has_error()) {
        minecraft::print_error(std::string("Failed to compile vertex shader: ") + vertex.get_error());
        glfwTerminate();
        return 1;
    }

    minecraft::Shader fragment(GL_FRAGMENT_SHADER, minecraft::slurp(std::ifstream("assets/shaders/main.fsh")));
    fragment.compile();
    if(fragment.has_error()) {
        minecraft::print_error(std::string("Failed to compile fragment shader: ") + fragment.get_error());
        glfwTerminate();
        return 1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    minecraft::Program program;
    program.link({vertex, fragment});

    vertex.remove();
    fragment.remove();

    float vertices[] = {
        // TOP
        0.5f, 0.5f, 0.5f, GRASS_TOP_RIGHT, GRASS_TOP_BOTTOM,
        0.5f, 0.5f, -0.5f, GRASS_TOP_RIGHT, GRASS_TOP_TOP,
        -0.5f, 0.5f, -0.5f, GRASS_TOP_LEFT, GRASS_TOP_TOP,
        -0.5f, 0.5f, 0.5f, GRASS_TOP_LEFT, GRASS_TOP_BOTTOM,

        // SOUTH
        0.5f, -0.5f, 0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_BOTTOM,
        0.5f, 0.5f, 0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_TOP,
        -0.5f, 0.5f, 0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_TOP,
        -0.5f, -0.5f, 0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_BOTTOM,

        // EAST
        0.5f, -0.5f, -0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_BOTTOM,
        0.5f, 0.5f, -0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_TOP,
        0.5f, 0.5f, 0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_TOP,
        0.5f, -0.5f, 0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_BOTTOM,

        // NORTH
        -0.5f, -0.5f, -0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_BOTTOM,
        -0.5f, 0.5f, -0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_TOP,
        0.5f, 0.5f, -0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_TOP,
        0.5f, -0.5f, -0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_BOTTOM,

        // WEST
        -0.5f, -0.5f, 0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_BOTTOM,
        -0.5f, 0.5f, 0.5f, GRASS_SIDE_RIGHT, GRASS_SIDE_TOP,
        -0.5f, 0.5f, -0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_TOP,
        -0.5f, -0.5f, -0.5f, GRASS_SIDE_LEFT, GRASS_SIDE_BOTTOM,

        // DOWN
        0.5f, -0.5f, -0.5f, DIRT_RIGHT, DIRT_BOTTOM,
        0.5f, -0.5f, 0.5f, DIRT_RIGHT, DIRT_TOP,
        -0.5f, -0.5f, 0.5f, DIRT_LEFT, DIRT_TOP,
        -0.5f, -0.5f, -0.5f, DIRT_LEFT, DIRT_BOTTOM
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    minecraft::Texture terrain("assets/textures/terrain.png");

    minecraft::Player player;
    
    glfwSetWindowUserPointer(window, &player);
    
    // hack for passing member func
    auto _mouse_fun = [](GLFWwindow* window, double x, double y) {
        static_cast<minecraft::Player*>(glfwGetWindowUserPointer(window))->handle_mouse(window, x, y);
    };

    glfwSetCursorPosCallback(window, _mouse_fun);

    // generate projection matrix
    float fov = 70.0f / 180 * (float) M_PI;
    float near = 0.1f, far = 100.0f;
    Eigen::Matrix4f projection;
    projection <<
        1 / (minecraft::window_width * 1.0f / minecraft::window_height * std::tan(fov / 2)), 0, 0, 0,
        0, 1 / (std::tan(fov / 2)), 0, 0,
        0, 0, -((far + near) / (far - near)), -((2 * far * near) / (far - near)),
        0, 0, -1, 0;

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)) {
        if(glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        // player handle inputs
        player.handle_inputs(window);

        // std::cout << "\x1b[2J" << player.get_x() << " " << player.get_y() << " " << player.get_z() << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, terrain.get_texture());

        program.use();

        glUniformMatrix4fv(glGetUniformLocation(program.get_program(), "projection"), 1, GL_FALSE, projection.data());
        glUniformMatrix4fv(glGetUniformLocation(program.get_program(), "view"), 1, GL_FALSE, player.generate_view_matrix().data());
        Eigen::Matrix4f identity = Eigen::Matrix4f::Identity();
        // std::cout << player.generate_view_matrix() << "\n";
        glUniformMatrix4fv(glGetUniformLocation(program.get_program(), "model"), 1, GL_FALSE, identity.data());

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    program.remove();

    glfwTerminate();

    return 0;
}
