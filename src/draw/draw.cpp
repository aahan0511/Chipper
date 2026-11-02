#include "draw.hpp"
#include "../display/display.hpp"
#include "../memory/memory.hpp"
#include "../cpu/cpu.hpp"

#include <cstdint>


void drawSprite(uint8_t x, uint8_t y, int height) {
    uint16_t addr = readIndex();

    for (int i = 0; i < height; i++) {
        uint8_t layer = readMemory(addr + i);

        int cur_x = x + 7;
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
