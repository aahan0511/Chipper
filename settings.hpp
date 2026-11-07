#pragma once

#include "raylib.h"

#include <cstdint>
#include <map>
#include <string>


// PLATFORM

    // true -> Cosmac VIP CHIP-8
        // CHIP-8 was first designed by Joseph Weisbecker for the Cosmac VIP hobbyist DIY computer in 1977. After publishing about the virtual instruction set in the december 1978 issue of Byte magazine (under the title \"An easy programming system\") it took off on more hobbyist computers. One of the biggest advantages of programming in CHIP-8, apart from being relatively easy to use, was the fact that CHIP-8 ROMs were binary compatible between several different hobbyist computers.
    // false -> Superchip 1.1
        // Superchip 1.1 is the platform that most \"superchip\" interpreters implement, because it is the latest version and also because the difference between Superchip version 1.0 and 1.1 is pretty small. This version is faster than its predecessor and adds scroll instructions and a large numeric font. It does however introduces a new quirk by not incrementing the index register when reading or writing registers to memory.
    constexpr bool PLATFORM_COSMIC = true;


// QUIRKS

    constexpr bool QUIRK_SHIFT                      = PLATFORM_COSMIC ? false   : true;
    constexpr bool QUIRK_MEMORY_INCREMENT_BY_X      = PLATFORM_COSMIC ? false   : false;
    constexpr bool QUIRK_MEMORY_LEAVE_I_UNCHANGED   = PLATFORM_COSMIC ? false   : true;
    constexpr bool QUIRK_WRAP                       = PLATFORM_COSMIC ? false   : false;
    constexpr bool QUIRK_JUMP                       = PLATFORM_COSMIC ? false   : true;
    constexpr bool QUIRK_VBLANK                     = PLATFORM_COSMIC ? true    : false;
    constexpr bool QUIRK_LOGIC                      = PLATFORM_COSMIC ? true    : false;

    // true -> Octo behaviour
    // false -> Original SUPERCHIP behaviour
    constexpr bool QUIRK_SUPERCHIP_CLEAR_ON_RES_CHANGE  = true;

    // keep this true unless you are absolutely sure you need to change this
    constexpr bool QUIRK_EXTRA_ADD_INDEX_LEAVE_F_UNCHANGED  = true; // https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#fx1e-add-to-index


// CPU SETTINGS

    constexpr int CPU_FREQ = 60;


// CLI SETTINGS

    constexpr std::string CLI_ERROR = "ERROR";
    constexpr std::string CLI_WARNING = "WARNING";
    constexpr std::string CLI_INFO = "INFO";
    constexpr std::string CLI_DEBUG = "DEBUG";


// DISPLAY SETTINGS

    constexpr int DISPLAY_TARGET_FPS = 60;
    constexpr int DISPLAY_PIXEL_SIZE = 30;

    constexpr Color PIXEL_OFF = BLACK;
    constexpr Color PIXEL_ON = WHITE;


// EXECUTION SETTINGS

    constexpr int EXECUTION_TARGET_STEPS = 60;      // maximum number of opcodes to run per frame
    constexpr int EXECUTION_CALL_STACK_DEPTH = 16;

    constexpr bool EXECUTION_WARN_FOR_0NNN = true;  // warn on use of opcodes designed to run machine code
    constexpr bool EXECUTION_WARN_FOR_8XYN = true;  // warn on use of class 8 opcodes outside the defined operations
    constexpr bool EXECUTION_WARN_FOR_E = true;     // warn on use of class E opcodes other than EX93 AND EXA1
    constexpr bool EXECUTION_WARN_FOR_F = true;     // warn on use of class F opcodes outside the defined set


// FONT SETTINGS
    // The inbuilt font can be configured at src/font/font_glyphs.hpp

    constexpr uint16_t FONT_LOAD_ADDRESS = 0x050;


// KEYPAD SETTINGS

    inline std::map<uint8_t, KeyboardKey> KEYPAD_MAP = {                        // Keypad Option 1
        {0x1, KEY_ONE}, {0x2, KEY_TWO}, {0x3, KEY_THREE}, {0xC, KEY_FOUR},      // 1 2 3 C - 1 2 3 4
        {0x4, KEY_Q},   {0x5, KEY_W},   {0x6, KEY_E},     {0xD, KEY_R},         // 4 5 6 D - Q W E R
        {0x7, KEY_A},   {0x8, KEY_S},   {0x9, KEY_D},     {0xE, KEY_F},         // 7 8 9 E - A S D F
        {0xA, KEY_Z},   {0x0, KEY_X},   {0xB, KEY_C},     {0xF, KEY_V},         // A 0 B F - Z X C V
    };

    // inline std::map<uint8_t, KeyboardKey> KEYPAD_MAP = {                     // Keypad Option 2
    //     {0x0, KEY_ONE}, {0x1, KEY_TWO}, {0x2, KEY_THREE}, {0x3, KEY_FOUR},   // 0 1 2 3 - 1 2 3 4
    //     {0x4, KEY_Q},   {0x5, KEY_W},   {0x6, KEY_E},     {0x7, KEY_R},      // 4 5 6 7 - Q W E R
    //     {0x8, KEY_A},   {0x9, KEY_S},   {0xA, KEY_D},     {0xB, KEY_F},      // 8 9 A B - A S D F
    //     {0xC, KEY_Z},   {0xD, KEY_X},   {0xE, KEY_C},     {0xF, KEY_V},      // C D E F - Z X C V
    // };


// MEMORY SETTINGS

    constexpr uint16_t MEMORY_ROM_LOAD_ADDRESS = 0x200;
