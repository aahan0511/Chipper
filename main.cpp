#include "src/display/display.hpp"
#include "src/cli/cli.hpp"
#include "src/files/files.hpp"
#include "src/memory/memory.hpp"
#include "src/execute/execute.hpp"

#include "raylib.h"

#include <cstdint>
#include <string>
#include <vector>


void init(std::vector<uint8_t> &rom) {
    initDisplay();
    loadROM(rom);
}

uint16_t loop(uint16_t steps) {
    execute();
    steps++;

    if (steps > TARGET_STEPS) {
        steps = 0;
        drawDisplay();
    }

    return steps;
}

void runtime(std::vector<uint8_t> &rom) {
    init(rom);

    uint16_t steps = 0;
    while (!WindowShouldClose()) {
        steps = loop(steps);
    }

    CloseWindow();
}


int main(int argc, char* args[]) {
    sprtrWithText("START");

        std::vector<uint8_t> rom = getROM(argc, args);

        info("running " + (std::string)args[1] + ".");

    drawSprtr();

        runtime(rom);

    sprtrWithText("END");
}
