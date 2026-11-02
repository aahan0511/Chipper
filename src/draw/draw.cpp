#include "draw.hpp"
#include "../display/display.hpp"
#include "../memory/memory.hpp"
#include "../cpu/cpu.hpp"

#include <cstdint>


void drawSprite(uint8_t x, uint8_t y, uint8_t height) {
    uint16_t addr = readIndex();

    for (uint8_t i = 0; i < height; i++) {
        uint8_t layer = readMemory(addr + i);

        uint8_t cur_x = x + 7;
        while (layer > 0) {
            if (layer % 2) {
                bool flipped_off = flipPixel(cur_x, y + i);
                if (flipped_off)
                    setRegister(0xF, 1);
            }
            layer /= 2;
            cur_x--;
        }
    }
}
