#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <glad/glad.h>

#include <iostream>
#include <cstdlib>
#include <string>

#include <boost/gil.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/extension/io/png.hpp>

namespace minecraft {

class Texture {
    public:
    Texture(std::string filename);

    GLuint get_texture();

    private:
    GLuint texture;
};

}

#endif
