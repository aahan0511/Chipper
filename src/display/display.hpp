#pragma once

#include <cstdint>


constexpr uint8_t SCREEN_WIDTH = 64;
constexpr uint8_t SCREEN_HEIGHT = 32;


void initDisplay();

bool checkDisplay();

void closeDisplay();


void displayEdit();

bool displayEdited();


void drawPixel(uint8_t x, uint8_t y);

void drawDisplay();


bool flipPixel(uint8_t x, uint8_t y);

void setPixelOn(uint8_t x, uint8_t y);

void setPixelOff(uint8_t x, uint8_t y);


void clearDisplay();
