#include "cpu.hpp"
#include "../memory/memory.hpp"

#include <cstdint>
#include <vector>


int PC = START_ADDR;

uint16_t setPC(int addr) {
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

void setRegister(int vx, uint8_t content) {
    registers[vx] = content;
}

uint8_t addToRegister(int vx, uint8_t content) {
    registers[vx] += content;
    return registers[vx];
}

uint8_t readRegister(int vx) {
    return registers[vx];
}


uint16_t index;

void setIndex(uint16_t content) {
    index = content;
}

uint16_t readIndex() {
    return index;
}
