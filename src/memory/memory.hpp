#pragma once

#include "../../settings.hpp"

#include <cstdint>
#include <vector>


void setMemory(uint16_t addr, uint8_t byt);

uint8_t readMemory(uint16_t addr);


void loadROM(std::vector<uint8_t> &rom, uint16_t addr = MEMORY_ROM_LOAD_ADDRESS);
