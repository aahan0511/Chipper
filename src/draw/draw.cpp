#include "draw.hpp"

#include "../../settings.hpp"

#include "../cpu/cpu.hpp"
#include "../display/display.hpp"
#include "../memory/memory.hpp"

#include <algorithm>
#include <cstdint>


void drawSprite(uint8_t x, uint8_t y, uint8_t height) {
    x %= SCREEN_WIDTH;
    y %= SCREEN_HEIGHT;

    setRegister(0xF, 0);
    uint16_t addr = readIndex();

    if (!QUIRK_WRAP) {
        height = std::min(y + height, (int)SCREEN_HEIGHT) - y;
    }

    for (uint8_t i = 0; i < height; i++) {
        uint8_t layer = readMemory((addr + i) % 0x1000);

        uint8_t width = 7;
        if (!QUIRK_WRAP) {
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


void drawSuperSprite(uint8_t x, uint8_t y, uint8_t height) {
    int screen_width = getRes() ? SCREEN_WIDTH / 2 : SCREEN_WIDTH;
    int screen_height = getRes() ? SCREEN_HEIGHT / 2 : SCREEN_HEIGHT;

    x %= screen_width;
    y %= screen_height;

    uint8_t collisions = 0;
    uint8_t clipped = 0;

    setRegister(0xF, 0);
    uint16_t addr = readIndex();

    if (height == 0) {
        height = 16;
        if (!QUIRK_WRAP) {
            height = std::min(y + 16, screen_height) - y;
            clipped = 16 - height;
        }

        uint8_t max_width = getRes() ? 7 : 15;

        for (uint8_t i = 0; i < height; i++) {
            bool flipped = false;

            uint16_t layer = (readMemory((addr + i * 2) % 0x1000) * 0b100000000) + readMemory((addr + i * 2 + 1) % 0x1000);
            if (getRes()) {
                layer = readMemory((addr + i) % 0x1000);
            }

            uint8_t width = max_width;
            if (!QUIRK_WRAP) {
                width = std::min(x + max_width, screen_width - 1) - x;
            }

            uint8_t cur_x = x + width;
            layer >>= (max_width - width);

            while (layer > 0) {
                if (layer % 2) {
                    bool flipped_off = flipPixel(cur_x % screen_width, (y + i) % screen_height);

                    if (flipped_off)
                        flipped = true;
                }
                layer /= 2;
                cur_x--;
            }

            if (flipped) collisions++;
        }

        if (getRes()) {
            setRegister(0xF, (collisions > 0) ? 1 : 0);
        } else {
            setRegister(0xF, collisions + clipped);
        }
    } else {
        if (!QUIRK_WRAP) {
            uint8_t full_height = height;
            height = std::min(y + height, screen_height) - y;
            clipped = full_height - height;
        }

        for (uint8_t i = 0; i < height; i++) {
            bool flipped = false;

            uint8_t layer = readMemory((addr + i) % 0x1000);

            uint8_t width = 7;
            if (!QUIRK_WRAP) {
                width = std::min(x + 7, screen_width - 1) - x;
            }

            uint8_t cur_x = x + width;
            layer >>= (7 - width);

            while (layer > 0) {
                if (layer % 2) {
                    bool flipped_off = flipPixel(cur_x % screen_width, (y + i) % screen_height);

                    if (flipped_off)
                        flipped = true;
                }
                layer /= 2;
                cur_x--;
            }

            if (flipped) collisions++;
        }

        if (getRes()) {
            setRegister(0xF, (collisions > 0) ? 1 : 0);
        } else {
            setRegister(0xF, collisions + clipped);
        }
    }
}


void scrollDown(uint8_t N) {
    if (getRes()) {
        if (QUIRK_SUPERCHIP_SCROLL_WHOLE_PIXEL_LORES)
            shiftDisplayDown((N % 0x10) * 2);
        else
            shiftDisplayDown((N % 0x10));
    } else {
        shiftDisplayDown(N % 0x10);
    }
}

void scrollRight() {
    if (getRes()) {
        if (QUIRK_SUPERCHIP_SCROLL_WHOLE_PIXEL_LORES)
            shiftDisplayRight(8);
        else
            shiftDisplayRight(4);
    } else {
        shiftDisplayRight(4);
    }
}

void scrollLeft() {
    if (getRes()) {
        if (QUIRK_SUPERCHIP_SCROLL_WHOLE_PIXEL_LORES)
            shiftDisplayLeft(8);
        else
            shiftDisplayLeft(4);
    } else {
        shiftDisplayLeft(4);
    }
}
