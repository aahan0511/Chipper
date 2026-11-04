#pragma once

#include "raylib.h"

#include <cstdint>
#include <map>

// 1 2 3 C - 1 2 3 4
// 4 5 6 D - Q W E R
// 7 8 9 E - A S D F
// A 0 B F - Z X C V
inline std::map<uint8_t, KeyboardKey> keyboard = {
    {0x1, KEY_ONE}, {0x2, KEY_TWO}, {0x3, KEY_THREE}, {0xC, KEY_FOUR},
    {0x4, KEY_Q},   {0x5, KEY_W},   {0x6, KEY_E},     {0xD, KEY_R},
    {0x7, KEY_A},   {0x8, KEY_S},   {0x9, KEY_D},     {0xE, KEY_F},
    {0xA, KEY_Z},   {0x0, KEY_X},   {0xB, KEY_C},     {0xF, KEY_V},
};


bool isKeyDown(uint8_t key);

bool isKeyUp(uint8_t key);


uint8_t anyKeyPressed();
