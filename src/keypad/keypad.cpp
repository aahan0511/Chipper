#include "keypad.hpp"

#include "raylib.h"

#include <cstdint>
#include <utility>
#include <set>


bool isKeyDown(uint8_t key) {
    return IsKeyDown(keyboard[key % 0x10]);
}

bool isKeyUp(uint8_t key) {
    return IsKeyUp(keyboard[key % 0x10]);
}


std::set<uint8_t> keys_down;

uint8_t anyKeyPressed() {
    for (uint8_t key : keys_down) {
        if (IsKeyUp(keyboard[key])) {
            keys_down.clear();
            return key;
        }
    }

    for (std::pair<uint8_t, KeyboardKey> key : keyboard) {
        if (IsKeyDown(key.second)) {
            keys_down.insert(key.first);
        }
    }

    return -1;
}
