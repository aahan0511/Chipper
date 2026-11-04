#include "draw.hpp"

#include "../cpu/cpu.hpp"
#include "../display/display.hpp"
#include "../memory/memory.hpp"
#include "../quirks/quirks.hpp"

#include <algorithm>
#include <cstdint>


void drawSprite(uint8_t x, uint8_t y, uint8_t height) {
    x %= SCREEN_WIDTH;
    y %= SCREEN_HEIGHT;

    setRegister(0xF, 0);
    uint16_t addr = readIndex();

    if (!(checkQuirk("wrap"))) {
        height = std::min(y + height, (int)SCREEN_HEIGHT) - y;
    }

    for (uint8_t i = 0; i < height; i++) {
        uint8_t layer = readMemory((addr + i) % 0x1000);

        uint8_t width = 7;
        if (!(checkQuirk("wrap"))) {
            width = std::min(x + 7, (int)(SCREEN_WIDTH - 1)) - x;
        }

        uint8_t cur_x = x + width;
        layer >>= (7 - width);

        while (layer > 0) {
            if (layer % 2) {
                bool flipped_off = flipPixel(cur_x % SCREEN_WIDTH, (y + i) % SCREEN_HEIGHT);

                if (flipped_off)
                    setRegister(0xF, 1);
            }
            layer /= 2;
            cur_x--;
        }
    }
}
