#pragma once

#include "raylib.h"

#include <cstdint>


constexpr uint8_t SCREEN_WIDTH = 64;
constexpr uint8_t SCREEN_HEIGHT = 32;
constexpr int PIXEL_SIZE = 30;
constexpr int TARGET_FPS = 60;

constexpr Color BG = BLACK;
constexpr Color FG = WHITE;

void initDisplay();


void drawPixel(uint8_t x, uint8_t y);

void drawDisplay();


void setPixel(uint8_t x, uint8_t y, Color color);

bool flipPixel(uint8_t x, uint8_t y);

void setPixelOn(uint8_t x, uint8_t y);

void setPixelOff(uint8_t x, uint8_t y);


void clearDisplay();
