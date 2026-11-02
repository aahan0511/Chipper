// Lines marked with `// *` are assisted by AI

#include "random.hpp"

#include <cstdint>
#include <random>


uint8_t generateRandom() {
    std::random_device rd;                                                  // *
    std::mt19937 generator(rd());                                           // *
    std::uniform_int_distribution<uint8_t> distrib(0b00000000, 0b11111111); // *

    return distrib(generator);  // *
}
