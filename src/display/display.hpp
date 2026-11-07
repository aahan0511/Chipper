#pragma once

#include "../../settings.hpp"

#include <cstdint>


constexpr uint8_t SCREEN_WIDTH = PLATFORM_COSMIC ? 64 : 128;
constexpr uint8_t SCREEN_HEIGHT = PLATFORM_COSMIC ? 32 : 64;


void initDisplay();

bool checkDisplay();

void closeDisplay();


void displayEdit();

bool displayEdited();


void drawPixel(uint8_t x, uint8_t y);

void drawDisplay();


void setLoRes();

void setHiRes();


bool flipPixel(uint8_t x, uint8_t y);


void clearDisplay();
