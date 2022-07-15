#include "shader.hpp"

namespace minecraft {

Shader::Shader(GLuint shader_type, std::string source) {
    this->shader_type = shader_type;
    this->shader = glCreateShader(shader_type);

    this->source_string = source;
    this->source_array = source.c_str();
    
    this->error = "";

    glShaderSource(this->shader, 1, &this->source_array, NULL);
}

void Shader::remove() {
    glDeleteShader(this->shader);
}

void Shader::compile() {
    glCompileShader(this->shader);

    int success;
    glGetShaderiv(this->shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char info_log[log_size + 10];
        glGetShaderInfoLog(this->shader, log_size, NULL, info_log);
        this->error = info_log;
    }
}

unsigned int Shader::get_shader() {
    return this->shader;
}

std::string Shader::get_error() {
    return this->error;
}

bool Shader::has_error() {
    return this->error != "";
}

void Shader::clear_error() {
    this->error = "";
}

}
