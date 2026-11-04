#include "src/cli/cli.hpp"
#include "src/files/files.hpp"
#include "src/runtime/runtime.hpp"

#include <cstdint>
#include <vector>


int main(int argc, char* args[]) {
    sprtrWithText("START");

        std::vector<uint8_t> rom = getROM(argc, args);

        info("running " + (std::string)args[1] + ".");

    drawSprtr();

        runtime(rom);

    sprtrWithText("END");
}
