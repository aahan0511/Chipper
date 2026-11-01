#pragma once

#include <cstdint>
#include <vector>


constexpr int START_ADDR = 0x200;

void setMemory(int addr, uint8_t byt);

uint8_t readMemory(int addr);

void loadROM(std::vector<uint8_t> &rom, int addr = START_ADDR);
