// Lines marked with `// *` are assisted by AI

#include "random.hpp"

#include <cstdint>
#include <random>


std::random_device rd;                                              // *
std::mt19937 generator(rd());                                       // *
std::uniform_int_distribution<int> distrib(0b00000000, 0b11111111); // *

uint8_t generateRandom() {
    return distrib(generator);  // *
}
