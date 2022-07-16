#include "chunk.hpp"

namespace minecraft {

Chunk::Chunk() {
    this->data = {BlockType::AIR}; 
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            this->data[i][j][8] = BlockType::GRASS_BLOCK;
        }
    }
}

const Chunk::chunk_data_t& Chunk::get_data() {
    return this->data;
}

void Chunk::set_block(int x, int y, int z, BlockType type) {
    this->data[x][z][y] = type;
}

}
