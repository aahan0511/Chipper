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
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = color;
}

bool flipPixel(int x, int y) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = ColorIsEqual(
        display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH], BG
    ) ? FG : BG;
    return ColorIsEqual(display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH], BG);
}

void setPixelOn(int x, int y) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = FG;
}

void setPixelOff(int x, int y) {
    display[y % SCREEN_HEIGHT][x % SCREEN_WIDTH] = BG;
}


void clearDisplay() {
    std::fill(display.begin(), display.end(), std::vector<Color>(SCREEN_WIDTH, BG));
}
