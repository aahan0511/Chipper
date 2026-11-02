#include "cpu.hpp"
#include "../memory/memory.hpp"

#include <cstdint>
#include <vector>


uint16_t PC = START_ADDR;

uint16_t setPC(uint16_t addr) {
    if (addr >= 4096)
        return -1;
    PC = addr;
    return (readMemory(PC) * 0x100) + readMemory(PC + 1);
}

uint16_t readPC() {
    uint16_t instruction = (readMemory(PC) * 0x100) + readMemory(PC + 1);

    if(instruction == 0x0000)
        return -1;
    return instruction;
}

uint16_t incrementPC() {
    if (PC + 2 >= 4096)
        return -1;
    PC += 2;
    return (readMemory(PC) * 0x100) + readMemory(PC + 1);
}


constexpr int REGISTER_N = 16;

std::vector<uint8_t> registers(16);

void setRegister(uint8_t vx, uint8_t content) {
    registers[vx] = content;
}

uint8_t addToRegister(uint8_t vx, uint8_t content) {
    registers[vx] += content;
    return registers[vx];
}

uint8_t readRegister(uint8_t vx) {
    return registers[vx];
}


uint16_t index;

void setIndex(uint16_t content) {
    index = content;
}

uint16_t readIndex() {
    return index;
}
