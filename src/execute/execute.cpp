#include "execute.hpp"
#include "../display/display.hpp"
#include "../cpu/cpu.hpp"
#include "../draw/draw.hpp"

#include <cstdint>


void execute(uint16_t opcode) {
    if (opcode == 0x00E0) {
        clearDisplay();

        incrementPC();
        return;
    }

    uint16_t code_type = opcode / 0x1000;
    uint16_t code_content = opcode % 0x1000;

    if (code_type == 0x0) {
        incrementPC();
        return;
    }

    if (code_type == 0x1) {
        setPC(code_content);
        return;
    }

    if (code_type == 0x6) {
        uint16_t vx = code_content / 0x100;
        uint16_t content = code_content % 0x100;

        setRegister(vx, content);

        incrementPC();
        return;
    }

    if (code_type == 0x7) {
        uint16_t vx = code_content / 0x100;
        uint16_t content = code_content % 0x100;

        addToRegister(vx, content);

        incrementPC();
        return;
    }

    if (code_type == 0xA) {
        setIndex(code_content);

        incrementPC();
        return;
    }

    if (code_type == 0xD) {
        uint8_t X, Y, N;
        X = code_content / 0x100;
        Y = (code_content % 0x100) / 0x10;
        N = (code_content % 0x10);

        uint8_t x = readRegister(X);
        uint8_t y = readRegister(Y);

        drawSprite(x, y, N);

        incrementPC();
        return;
    }
}
