#include "memory.hpp"

#include <cstdint>
#include <vector>


constexpr int MEMORY_SIZE = 4096;

std::vector<uint8_t> memory(MEMORY_SIZE);

void setMemory(uint16_t addr, uint8_t byt) {
    memory[addr] = byt;
}

uint8_t readMemory(uint16_t addr) {
    return memory[addr];
}


void loadROM(std::vector<uint8_t> &rom, uint16_t addr) {
    for (uint8_t byt : rom) {
        memory[addr++] = byt;
    }
}
