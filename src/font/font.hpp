#pragma once

#include <cstdint>


inline constexpr uint16_t FONT_START_ADDR = 0x050;

void loadFont(uint16_t startAddr = FONT_START_ADDR);


uint16_t getFontAddr(uint8_t c);
