#include "execute.hpp"
#include "../display/display.hpp"
#include "../cpu/cpu.hpp"
#include "../draw/draw.hpp"

#include <cstdint>
#include <stack>


std::stack<uint16_t> call_stack;

void addCall(uint16_t call) {
    call_stack.push(call);
}

uint16_t popCall() {
    uint16_t call = call_stack.top();
    call_stack.pop();

    return call;
}


void execute() {
    uint16_t opcode = readPC();

    uint16_t code_type = opcode / 0x1000;
    uint16_t code_content = opcode % 0x1000;

    if (code_type == 0x0) {
        if (opcode == 0x00E0) {
            clearDisplay();
        } else if (0x00EE) {
            returnPC();
        }

        incrementPC();
        return;
    }

    if (code_type == 0x1) {
        setPC(code_content);
        return;
    }

    if (code_type == 0x2) {
        stackPC(code_content);
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
