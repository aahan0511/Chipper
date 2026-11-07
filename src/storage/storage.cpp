#include "storage.hpp"

#include "../../settings.hpp"

#include "../cli/cli.hpp"
#include "../cpu/cpu.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>


std::vector<uint8_t> flags(16, 0);

void readFlagsFile() {
    if (!std::filesystem::exists(STORAGE_FILE))                                     // *
        return;     // first run, flags stay 0                                      // *
                                                                                    // *
    std::ifstream file(STORAGE_FILE, std::ios::binary);                             // *
    if (!file) {                                                                    // *
        warning("could not open \"" + STORAGE_FILE.string() + "\" to read flags."); // *
        return;                                                                     // *
    }                                                                               // *
                                                                                    // *
    file.read(reinterpret_cast<char*>(flags.data()), flags.size());                 // *
}


void writeFlagsFile() {
    std::ofstream file(STORAGE_FILE, std::ios::binary | std::ios::trunc);           // *
    if (!file) {                                                                    // *
        warning("could not open \"" + STORAGE_FILE.string() + "\" to save flags."); // *
        return;                                                                     // *
    }                                                                               // *
                                                                                    // *
    file.write(reinterpret_cast<const char*>(flags.data()), flags.size());          // *
    if (!file)                                                                      // *
        warning("failed to write flags to \"" + STORAGE_FILE.string() + "\".");     // *
}


void saveToFlags(uint8_t X) {
    for (int VX = 0; VX <= X; VX++)
        flags[VX] = readRegister(VX);

    writeFlagsFile();
}

void loadFromFlags(uint8_t X) {
    for (int VX = 0; VX <= X; VX++)
        setRegister(VX, flags[VX]);
}
