#include "src/cli/cli.hpp"
#include "src/files/files.hpp"
#include "src/runtime/runtime.hpp"

#include <cstdint>
#include <string>
#include <vector>


int main(int argc, char* args[]) {
        std::pair<std::vector<uint8_t>, std::string> rom_file = getROM(argc, args);
        std::vector<uint8_t> rom = rom_file.first;
        std::string file_label = rom_file.second;

    setFileLabel(file_label);
    sprtrWithText("START: " + file_label);

        info("running " + (std::string)args[1] + ".");

    drawSprtr();

        runtime(rom);

    sprtrWithText("END: " + getFileLabel());
}
