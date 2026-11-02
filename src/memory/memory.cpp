#include "memory.hpp"
#include "../cli/cli.hpp"

#include <cstdint>
#include <vector>


std::vector<uint8_t> memory(MEMORY_SIZE);

void setMemory(uint16_t addr, uint8_t byt) {
    if (addr >= MEMORY_SIZE || addr < 0)
        error("memory out of bounds");
    memory[addr] = byt;
}

uint8_t readMemory(uint16_t addr) {
    if (addr >= MEMORY_SIZE || addr < 0)
        error("memory out of bounds");
    return memory[addr];
}


void loadROM(std::vector<uint8_t> &rom, uint16_t addr) {
    if (addr >= MEMORY_SIZE || addr < 0)
        error("memory out of bounds");

    if (rom.size() > 4096 - addr)
        error("ROM does not fit in memory.");

    for (uint8_t byt : rom) {
        memory[addr++] = byt;
    }
}
