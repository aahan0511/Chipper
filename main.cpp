#include "src/display/display.hpp"
#include "src/cli/cli.hpp"

#include "raylib.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


void init() {
    initDisplay();
}

void loop() {

}

void runtime(std::vector<std::string> &lines) {
    init();

    while (!WindowShouldClose()) {
        loop();

        drawDisplay();
    }

    CloseWindow();
}

int main(int argc, char* args[]) {
    sprtrWithText("START");

        if (argc == 1) {
            std::cout << ERROR << ": please provide a chip-8 file to execute." << "\n";

            sprtrWithText("END");
            return 1;
        }

        std::string file_path = args[1];
        if (argc > 2) {
            std::cout << WARNING << ": only considering the first file (\"" << file_path << "\")." << "\n";
        }

        std::ifstream file(file_path);
        if (!file.good()) {
            std::cout << ERROR << ": file (\"" << file_path << "\") does not exist." << "\n";

            sprtrWithText("END");
            return 1;
        }

        std::cout << INFO << ": running " << file_path << "." << "\n";

        std::vector<std::string> lines;
        std::string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }

    drawSprtr();

        runtime(lines);

    sprtrWithText("END");
}
