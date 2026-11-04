#include "runtime.hpp"

#include "../display/display.hpp"
#include "../execute/execute.hpp"
#include "../font/font.hpp"
#include "../memory/memory.hpp"
#include "../quirks/quirks.hpp"
#include "../sound/sound.hpp"
#include "../timer/timer.hpp"

#include <cstdint>
#include <vector>


bool initialized = false;

bool checkInit() {
    return initialized;
}

void init(std::vector<uint8_t> &rom) {
    initDisplay();
    initAudio();
    loadQuirks();
    initialized = true;

    loadFont();
    loadROM(rom);
}

void deinit() {
    closeDisplay();
    closeAudio();

    initialized = false;
}


uint16_t loop(uint16_t steps) {
    execute();
    steps++;

    if (steps >= TARGET_STEPS || (displayEdited() && checkQuirk("vblank"))) {
        steps = 0;
        drawDisplay();

        if (checkSoundTimer())
            playSound();
        else
            stopSound();
    }

    return steps;
}


void runtime(std::vector<uint8_t> &rom) {
    init(rom);

    uint16_t steps = 0;
    while (checkDisplay()) {
        steps = loop(steps);
    }

    deinit();
}
