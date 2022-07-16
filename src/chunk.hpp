#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include "blocks.hpp"

#include <array>

namespace minecraft {

class Chunk {
    public:
    using chunk_data_t = std::array<std::array<std::array<int, 256>, 16>, 16>;
    // x then z then y
    Chunk();
    chunk_data_t& get_data();
    void set_block(int x, int y, int z);

    private:
    chunk_data_t data;
};

}

#endif
