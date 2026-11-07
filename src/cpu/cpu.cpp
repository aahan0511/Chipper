#include "cpu.hpp"

#include "../../settings.hpp"

#include "../cli/cli.hpp"
#include "../execute/execute.hpp"
#include "../memory/memory.hpp"

#include <cstdint>
#include <vector>


uint16_t PC = MEMORY_ROM_LOAD_ADDRESS;

void setPC(uint16_t addr) {
    PC = addr % 0x1000;
}

uint16_t readPC() {
    uint16_t instruction = (readMemory(PC % 0x1000) * 0x100) + readMemory((PC + 1) % 0x1000);

    return instruction;
}

void incrementPC() {
    PC += 2;
}

void decrementPC() {
    PC -= 2;
}


void stackPC(uint16_t call) {
    addCall(PC);
    setPC(call);
}

void returnPC() {
    setPC(popCall());
}


std::vector<uint8_t> registers(16);

void setRegister(uint8_t vx, uint8_t content) {
    if (vx > 0xF || vx < 0)
        error("register out of bounds");
    registers[vx] = content;
}

uint8_t addToRegister(uint8_t vx, uint8_t content) {
    if (vx > 0xF || vx < 0)
        error("register out of bounds");
    registers[vx] += content;
    return registers[vx];
}

uint8_t readRegister(uint8_t vx) {
    if (vx > 0xF || vx < 0)
        error("register out of bounds");
    return registers[vx];
}


uint16_t index_register;

void setIndex(uint16_t content) {
    index_register = content;
}

bool addToIndex(uint8_t content) {
    int sum = readIndex() + content;
    index_register = sum % 0x1000;
    return sum > 0xFFF;
}

uint16_t readIndex() {
    return index_register;
}

void updateIndexUpdate(int X) {
    if (QUIRK_MEMORY_LEAVE_I_UNCHANGED)
        return;

    if (QUIRK_MEMORY_INCREMENT_BY_X) {
        setIndex(readIndex() + X);
    } else {
        setIndex(readIndex() + X + 1);
    }
}
