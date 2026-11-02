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


std::vector<uint8_t> getROM(int argc, char* args[]) {
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

    std::vector<uint8_t> rom(size);                         // *
    file.read(reinterpret_cast<char*>(rom.data()), size);   // *

    return rom;
}
