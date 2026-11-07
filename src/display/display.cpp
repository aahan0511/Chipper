#include "display.hpp"

#include "../../settings.hpp"

#include "raylib.h"

#include <algorithm>
#include <vector>


void initDisplay() {
    InitWindow(
        SCREEN_WIDTH * DISPLAY_PIXEL_SIZE,
        SCREEN_HEIGHT * DISPLAY_PIXEL_SIZE,
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
        x * DISPLAY_PIXEL_SIZE,
        y * DISPLAY_PIXEL_SIZE,
        DISPLAY_PIXEL_SIZE,
        DISPLAY_PIXEL_SIZE,
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


bool flipPixel(uint8_t x, uint8_t y) {
    display[y][x] = !(display[y][x]);

    return !(display[y][x]);
}

void setPixelOn(uint8_t x, uint8_t y) {
    display[y][x] = 1;
}

void setPixelOff(uint8_t x, uint8_t y) {
    display[y][x] = 0;
}


void clearDisplay() {
    std::fill(display.begin(), display.end(), std::vector<bool>(SCREEN_WIDTH, 0));
}
