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

    for (uint8_t x = 0; x < SCREEN_WIDTH; x++)
        for (uint8_t y = 0; y < SCREEN_HEIGHT; y++)
            drawPixel(x, y);

    EndDrawing();
    resetDisplayStatus();
}


void setPixel(uint8_t x, uint8_t y, Color color) {
    display[y][x] = color;
}

bool flipPixel(uint8_t x, uint8_t y) {
    display[y][x] = ColorIsEqual(
        display[y][x], BG
    ) ? FG : BG;

    return ColorIsEqual(display[y][x], BG);
}

void setPixelOn(uint8_t x, uint8_t y) {
    display[y][x] = FG;
}

void setPixelOff(uint8_t x, uint8_t y) {
    display[y][x] = BG;
}


void clearDisplay() {
    std::fill(display.begin(), display.end(), std::vector<Color>(SCREEN_WIDTH, BG));
}
