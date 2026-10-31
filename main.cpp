#include "src/display/display.hpp"
#include "src/cli/cli.hpp"
#include "src/files/files.hpp"

#include "raylib.h"

#include <cstdint>
#include <string>
#include <vector>


void init() {
    initDisplay();
}

void loop() {

}

void runtime(std::vector<uint16_t> &rom) {
    init();

    while (!WindowShouldClose()) {
        loop();

        drawDisplay();
    }

    CloseWindow();
}

int main(int argc, char* args[]) {
    sprtrWithText("START");

        std::vector<uint16_t> rom = getROM(argc, args);

        info("running " + (std::string)args[1] + ".");

    drawSprtr();

        runtime(rom);

    sprtrWithText("END");
}
