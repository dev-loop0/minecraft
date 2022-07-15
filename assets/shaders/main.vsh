#version 330

layout(location = 0) in vec3 my_pos;
layout(location = 1) in vec2 my_tex_coord;

varying vec2 our_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(my_pos, 1.0f);
    // gl_Position = vec4(my_pos, 1.0f);
    our_tex_coord = my_tex_coord;
}
