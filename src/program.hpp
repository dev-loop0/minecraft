#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "shader.hpp"

namespace minecraft {

class Program {
    public:

    Program();
    void remove();

    void link(std::vector<minecraft::Shader> shaders);
    void use();

    GLuint get_program();

    std::string get_error();
    bool has_error();
    void clear_error();

    private:
    GLuint program;
    std::string error;
};

}

#endif
