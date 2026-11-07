#include "display.hpp"

#include "../../settings.hpp"

#include "raylib.h"

#include <algorithm>
#include <cstdint>
#include <vector>


constexpr int PIXEL_SIZE = PLATFORM_COSMIC ? DISPLAY_PIXEL_SIZE : (DISPLAY_PIXEL_SIZE / 2);


void initDisplay() {
    InitWindow(
        SCREEN_WIDTH * PIXEL_SIZE,
        SCREEN_HEIGHT * PIXEL_SIZE,
        "Chipper"
    );

    SetTargetFPS(DISPLAY_TARGET_FPS);

    clearDisplay();
    drawDisplay();
}

bool checkDisplay() {
    return !(WindowShouldClose());
}

void closeDisplay() {
    CloseWindow();
}


bool edited_display = true;

void displayEdit() {
    edited_display = true;
}

bool displayEdited() {
    return edited_display;
}

void resetDisplayStatus() {
    edited_display = false;
}


std::vector<std::vector<bool>> display(SCREEN_HEIGHT, std::vector<bool>(SCREEN_WIDTH, 0));

void drawPixel(uint8_t x, uint8_t y) {
    DrawRectangle(
        x * PIXEL_SIZE,
        y * PIXEL_SIZE,
        PIXEL_SIZE,
        PIXEL_SIZE,
        display[y][x] ? PIXEL_ON : PIXEL_OFF
    );
}

void drawDisplay() {
    BeginDrawing();

    for (uint8_t x = 0; x < SCREEN_WIDTH; x++)
        for (uint8_t y = 0; y < SCREEN_HEIGHT; y++)
            drawPixel(x, y);

    EndDrawing();
    resetDisplayStatus();
}


inline bool lores = true;

bool getRes() {
    return lores;
}

void setLoRes() {
    lores = true;
    if (QUIRK_SUPERCHIP_CLEAR_ON_RES_CHANGE) {
        clearDisplay();
    }
}

void setHiRes() {
    lores = false;
    if (QUIRK_SUPERCHIP_CLEAR_ON_RES_CHANGE) {
        clearDisplay();
    }
}


bool flipPixel(uint8_t x, uint8_t y) {
    if (PLATFORM_COSMIC) {
        display[y][x] = !(display[y][x]);

        return !(display[y][x]);
    } else {
        if (lores) {
            x *= 2;
            y *= 2;

            display[y][x] = !(display[y][x]);
            display[y + 1][x] = !(display[y + 1][x]);
            display[y][x + 1] = !(display[y][x + 1]);
            display[y + 1][x + 1] = !(display[y + 1][x + 1]);

            return (!(display[y][x]) || !(display[y + 1][x]) || !(display[y][x + 1]) || !(display[y + 1][x + 1]));
        } else {
            display[y][x] = !(display[y][x]);

            return !(display[y][x]);
        }
    }
}


void clearDisplay() {
    std::fill(display.begin(), display.end(), std::vector<bool>(SCREEN_WIDTH, 0));
}
