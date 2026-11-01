#include "cpu.hpp"
#include "../memory/memory.hpp"

#include <cstdint>


int PC = START_ADDR;

uint16_t setPC(int addr) {
    if (addr >= 4096) {
        return -1;
    }
    PC = addr;
    return (readMemory(PC) * 0x100) + readMemory(PC + 1);
}

uint16_t readPC() {
    uint16_t instruction = (readMemory(PC) * 0x100) + readMemory(PC + 1);

    if(instruction == 0x0000) return -1;
    return instruction;
}

uint16_t incrementPC() {
    if (PC + 2 >= 4096) {
        return -1;
    }
    PC += 2;
    return (readMemory(PC) * 0x100) + readMemory(PC + 1);
}
