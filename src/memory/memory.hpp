#pragma once

#include <cstdint>
#include <vector>


void setMemory(uint16_t addr, uint8_t byt);

uint8_t readMemory(uint16_t addr);


constexpr uint16_t START_ADDR = 0x200;

void loadROM(std::vector<uint8_t> &rom, uint16_t addr = START_ADDR);
