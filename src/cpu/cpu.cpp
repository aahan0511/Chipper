#include "cpu.hpp"
#include "../memory/memory.hpp"
#include "../execute/execute.hpp"
#include "../cli/cli.hpp"

#include <cstdint>
#include <vector>


uint16_t PC = START_ADDR;

void setPC(uint16_t addr) {
    PC = addr;
}

uint16_t readPC() {
    uint16_t instruction = (readMemory(PC) * 0x100) + readMemory(PC + 1);

    if (instruction == 0x0000)
        error("program counter went outside of loaded rom");
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


constexpr int REGISTER_N = 16;

std::vector<uint8_t> registers(REGISTER_N);

void setRegister(uint8_t vx, uint8_t content) {
    if (vx >= REGISTER_N || vx < 0)
        error("register out of bounds");
    registers[vx] = content;
}

uint8_t addToRegister(uint8_t vx, uint8_t content) {
    if (vx >= REGISTER_N || vx < 0)
        error("register out of bounds");
    registers[vx] += content;
    return registers[vx];
}

uint8_t readRegister(uint8_t vx) {
    if (vx >= REGISTER_N || vx < 0)
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
