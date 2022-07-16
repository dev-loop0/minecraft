#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include "blocks.hpp"

#include <array>

namespace minecraft {

class Chunk {
    public:
    // array indexing: x then z then y
    using chunk_data_t = std::array<std::array<std::array<BlockType, 256>, 16>, 16>;
    
    Chunk();

    const chunk_data_t& get_data();
    void set_block(int x, int y, int z, BlockType type);

    private:
    chunk_data_t data;
};

}

#endif
