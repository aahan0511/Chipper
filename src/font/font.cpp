#include "font.hpp"

#include "font_glyphs.hpp"
#include "../../settings.hpp"

#include "../memory/memory.hpp"

#include <cstdint>


void loadFont(uint16_t startAddr) {
    for (uint8_t glyph = 0x0; glyph <= 0xF; glyph++) {
        for (uint8_t byt : FONT_GLYPHS[glyph]) {
            setMemory(startAddr, byt);
            startAddr++;
        }
    }
}

void loadBigFont(uint16_t startAddr) {
    for (uint8_t glyph = 0x0; glyph <= 0xF; glyph++) {
        for (uint8_t byt : BIG_FONT_GLYPHS[glyph]) {
            setMemory(startAddr, byt);
            startAddr++;
        }
    }
}


uint16_t getFontAddr(uint8_t c) {
    c %= 0x10;

    return FONT_LOAD_ADDRESS + (c * 5);
}

uint16_t getBigFontAddr(uint8_t c) {
    c %= 0x10;

    return BIG_FONT_LOAD_ADDRESS + (c * 10);
}
