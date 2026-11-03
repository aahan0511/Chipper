#pragma once

#include <cstdint>


inline constexpr double FREQ = 60;


void setDelayTimer(uint8_t content);

uint8_t readDelayTimer();


void setSoundTimer(uint8_t content);

bool checkSoundTimer();
