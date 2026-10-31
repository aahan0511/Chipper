#include "src/display/display.hpp"

#include "raylib.h"


void init() {
    initDisplay();
}

void loop() {

}

int main() {
    init();

    while (!WindowShouldClose()) {
        loop();

        drawDisplay();
    }

    CloseWindow();
}
