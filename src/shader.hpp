#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

namespace minecraft {

constexpr size_t log_size = 1024;

class Shader {
    public:

    Shader(GLuint shader_type, std::string source);
    void remove();

    void compile();

    unsigned int get_shader();

    std::string get_error();
    bool has_error();
    void clear_error();

    private:
    GLuint shader_type;
    std::string source_string;
    const char* source_array;
    GLuint shader;
    std::string error;
};

}

#endif
