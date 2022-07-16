#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <glad/glad.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "chunk.hpp"

namespace minecraft {

class World {
    public:
    World();

    void make_vertices();

    void generate(int x, int z);

    private:
    std::map<std::pair<int, int>, Chunk> chunks;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

}

#endif
