#version 330

out vec4 FragColor;

varying vec2 our_tex_coord;

uniform sampler2D _texture;

void main() {
    FragColor = texture(_texture, our_tex_coord);
}
