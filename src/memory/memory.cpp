#include "memory.hpp"

#include <cstdint>
#include <vector>


constexpr int MEMORY_SIZE = 4096;

std::vector<uint8_t> memory(MEMORY_SIZE);

void setMemory(int addr, uint8_t byt) {
    memory[addr] = byt;
}

uint8_t readMemory(int addr) {
    return memory[addr];
}
