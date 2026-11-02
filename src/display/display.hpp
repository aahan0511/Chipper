#pragma once

#include "raylib.h"


constexpr int SCREEN_WIDTH = 64;
constexpr int SCREEN_HEIGHT = 32;
constexpr int PIXEL_SIZE = 30;
constexpr int TARGET_FPS = 60;

constexpr Color BG = BLACK;
constexpr Color FG = WHITE;

void initDisplay();

void drawDisplay();


void setPixel(int x, int y, Color color);

bool flipPixel(int x, int y);

void setPixelOn(int x, int y);

void setPixelOff(int x, int y);


void clearDisplay();
