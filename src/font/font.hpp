#pragma once

#include "../../settings.hpp"

#include <cstdint>


void loadFont(uint16_t startAddr = FONT_LOAD_ADDRESS);


uint16_t getFontAddr(uint8_t c);
