#include "texture.hpp"

namespace minecraft {

Texture::Texture(std::string filename) {
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    boost::gil::rgba8_image_t image;
    boost::gil::read_image(filename, image, boost::gil::png_tag());
    int width = image.width(), height = image.height();
    uint8_t* data = new uint8_t[4 * width * height];
    int row = height - 1, column = 0;
    boost::gil::for_each_pixel(boost::gil::const_view(image), [data, &row, &column, width](boost::gil::rgba8_pixel_t pixel) {
        if(column == width) {
            column = 0;
            row--;
        }
        data[4 * (row * width + column)] = boost::gil::at_c<0>(pixel);
        data[4 * (row * width + column) + 1] = boost::gil::at_c<1>(pixel);
        data[4 * (row * width + column) + 2] = boost::gil::at_c<2>(pixel);
        data[4 * (row * width + column) + 3] = boost::gil::at_c<3>(pixel);
        column++;
    });
    
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    delete data;
}

GLuint Texture::get_texture() {
    return this->texture;
}

}
