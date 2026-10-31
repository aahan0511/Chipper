// Lines marked with `// *` are AI-generated

#include "files.hpp"
#include "../cli/cli.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


void checkFile(std::string file_name, std::filesystem::path file_path) {
    if (!std::filesystem::exists(file_path))
        error("\"" + file_name + "\" does not exist.");

    if (!std::filesystem::is_regular_file(file_path))
        error("\"" + file_name + "\" is not a regular file.");

    std::string extension = file_path.extension().string();
    if (extension != ".ch8" && extension != ".c8" && extension != ".chip8")
        warning("\"" + file_name + "\" might not be a CHIP-8 ROM.");
}

std::vector<uint16_t> getROM(int argc, char* args[]) {
    if (argc == 1) {
        error("please provide a chip-8 file to execute.");
    }

    std::string file_name = args[1];
    std::filesystem::path file_path(file_name);
    if (argc > 2)
        warning("only considering the first file (\"" + file_name + "\").");

    checkFile(file_name, file_path);

    std::ifstream file(file_name, std::ios::binary | std::ios::ate);    // *

    std::streamsize size = file.tellg();    // *
    file.seekg(0, std::ios::beg);           // *

    if (size <= 0) {
        error("failed to read ROM.");
    }

    if (size > 4096 - 0x200) {
        error("ROM does not fit in memory.");
    }

    std::vector<uint8_t> byte_rom(size);                         // *
    file.read(reinterpret_cast<char*>(byte_rom.data()), size);   // *

    std::vector<uint16_t> rom(size / 2);
    for (int i = 0; i < size; i += 2) {
        rom[i / 2] = byte_rom[i] + byte_rom[i + 1];
    }

    return rom;
}
