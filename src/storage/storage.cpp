#include "storage.hpp"

#include "../cpu/cpu.hpp"

#include <cstdint>
#include <vector>


std::vector<uint8_t> flags(16, 0);

void saveToFlags(uint8_t X) {
    for (int VX = 0; VX <= X; VX++)
        flags[VX] = readRegister(VX);
}

void loadFromFlags(uint8_t X) {
    for (int VX = 0; VX <= X; VX++)
        setRegister(VX, flags[VX]);
}
