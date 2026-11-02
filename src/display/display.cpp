#include "display.hpp"

#include "raylib.h"

#include <algorithm>
#include <vector>


void initDisplay() {
    InitWindow(
        SCREEN_WIDTH * PIXEL_SIZE,
        SCREEN_HEIGHT * PIXEL_SIZE,
        "Chipper"
    );

    SetTargetFPS(TARGET_FPS);
    ClearBackground(BG);
}

bool editted_display = true;

void displayEdit() {
    editted_display = true;
}

bool displayChanged() {
    return editted_display;
}

void resetDisplayStatus() {
    editted_display = false;
}


std::vector<std::vector<Color>> display(SCREEN_HEIGHT, std::vector<Color>(SCREEN_WIDTH, BG));

void drawPixel(uint8_t x, uint8_t y) {
    DrawRectangle(
        x * PIXEL_SIZE,
        y * PIXEL_SIZE,
        PIXEL_SIZE,
        PIXEL_SIZE,
        display[y][x]
    );
}

void drawDisplay() {
    BeginDrawing();

    if (displayChanged()) {
        for (uint8_t x = 0; x < SCREEN_WIDTH; x++)
            for (uint8_t y = 0; y < SCREEN_HEIGHT; y++)
                drawPixel(x, y);
    }

    EndDrawing();

    resetDisplayStatus();
}


void setPixel(uint8_t x, uint8_t y, Color color) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = color;
}

bool flipPixel(uint8_t x, uint8_t y) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = ColorIsEqual(
        display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH], BG
    ) ? FG : BG;

    return ColorIsEqual(display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH], BG);
}

void setPixelOn(uint8_t x, uint8_t y) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = FG;
}

void setPixelOff(uint8_t x, uint8_t y) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = BG;
}


void clearDisplay() {
    std::fill(display.begin(), display.end(), std::vector<Color>(SCREEN_WIDTH, BG));
}
