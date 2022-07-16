#include "world.hpp"

namespace minecraft {

World::World() {
    this->generate(0, 0);
}

void World::make_vertices() {
    this->vertices.clear();
    this->indices.clear();

    for(auto i = this->chunks.begin(); i != this->chunks.end(); i++) {
        const Chunk::chunk_data_t& data = i->second.get_data();
        for(int x = 0; x < 16; x++) {
            for(int z = 0; z < 16; z++) {
                for(int y = 0; y < 256; y++) {
                    if(data[x][z][y] == BlockType::GRASS_BLOCK) {
                        this->vertices.push_back();
                        this->vertices.push_back();
                        this->vertices.push_back();
                        this->vertices.push_back();
                        this->vertices.push_back();
                    }
                }
            }
        }
    }
}

void World::generate(int x, int z) {
    if(x == 0 && z == 0)
    this->chunks[std::pair(x, z)] = Chunk();
}

}
