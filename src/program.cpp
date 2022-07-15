#include "program.hpp"

namespace minecraft {

Program::Program()  {
    this->error = "";

    this->program = glCreateProgram();
}

void Program::remove() {
    glDeleteProgram(this->program);
}

void Program::link(std::vector<minecraft::Shader> shaders) {
    for(minecraft::Shader& i : shaders){
        glAttachShader(this->program, i.get_shader());
    }
    glLinkProgram(this->program);

    char info_log[::minecraft::log_size];
    int success;
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(this->program, ::minecraft::log_size, NULL, info_log);
        this->error = info_log;
    }
}

void Program::use() {
    glUseProgram(this->program);
}

GLuint Program::get_program() {
    return this->program;
}

std::string Program::get_error() {
    return this->error;
}

bool Program::has_error() {
    return this->error != "";
}

void Program::clear_error() {
    this->error = "";
}

}