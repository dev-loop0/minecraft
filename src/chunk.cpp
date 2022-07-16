#include "chunk.hpp"

namespace minecraft {

Chunk::Chunk() {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            this->data[i][j][8] = GRASS_BLOCK;
        }
    }
}

}
