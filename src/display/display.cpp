#include "display.hpp"

#include "raylib.h"

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

std::vector<std::vector<Color>> display(SCREEN_HEIGHT, std::vector<Color>(SCREEN_WIDTH, BG));

void drawDisplay() {
    BeginDrawing();
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            for (int y = 0; y < SCREEN_HEIGHT; y++) {
                DrawRectangle(
                    x * PIXEL_SIZE,
                    y * PIXEL_SIZE,
                    PIXEL_SIZE,
                    PIXEL_SIZE,
                    display[y][x]
                );
            }
        }
    EndDrawing();
}

void setPixel(int x, int y, Color color) {
    display[y][x] = color;
}

void setPixelOn(int x, int y) {
    display[y][x] = FG;
}

void setPixelOff(int x, int y) {
    display[y][x] = BG;
}
