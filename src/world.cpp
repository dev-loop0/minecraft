#include "world.hpp"

namespace minecraft {

World::World() {
    this->generate(0, 0);
}

void World::make_vertices() {
    this->vertices.clear();
    this->indices.clear();

    for(auto i = this->chunks.begin(); i != this->chunks.end(); i++) {
        
    }
}

void World::generate(int x, int z) {
    if (x == 0 && z == 0)
    this->chunks[std::pair(x, z)] = Chunk();
}

}
