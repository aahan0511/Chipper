#include "execute.hpp"
#include "../display/display.hpp"
#include "../cpu/cpu.hpp"
#include "../draw/draw.hpp"
#include "../cli/cli.hpp"

#include <cstdint>
#include <stack>
#include <string>


std::stack<uint16_t> call_stack;

void addCall(uint16_t call) {
    call_stack.push(call);
}

uint16_t popCall() {
    if (call_stack.size() == 0)
        error("call stack empty");

    uint16_t call = call_stack.top();
    call_stack.pop();

    return call;
}


void execute() {
    uint16_t opcode = readPC();
    incrementPC();

    uint16_t code_type = opcode / 0x1000;
    uint16_t code_content = opcode % 0x1000;

    if (code_type == 0x0) {
        if (opcode == 0x00E0) {
            clearDisplay();
            displayEdit();
        }

        if (opcode == 0x00EE) {
            returnPC();
        }

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

    if (code_type == 0x3) {
        uint8_t X = code_content / 0x100;
        uint8_t NN = code_content % 0x100;

        uint8_t x = readRegister(X);
        if (x == NN) incrementPC();

        return;
    }

    if (code_type == 0x4) {
        uint8_t X = code_content / 0x100;
        uint8_t NN = code_content % 0x100;

        uint8_t x = readRegister(X);
        if (x != NN) incrementPC();

        return;
    }

    if (code_type == 0x5) {
        uint8_t X = code_content / 0x100;
        uint8_t Y = (code_content % 0x100) / 0x10 ;

        uint8_t x = readRegister(X);
        uint8_t y = readRegister(Y);
        if (x == y) incrementPC();

        return;
    }

    if (code_type == 0x6) {
        uint16_t vx = code_content / 0x100;
        uint16_t content = code_content % 0x100;

        setRegister(vx, content);
        return;
    }

    if (code_type == 0x7) {
        uint16_t vx = code_content / 0x100;
        uint16_t content = code_content % 0x100;

        addToRegister(vx, content);
        return;
    }

    if (code_type == 0x8) {

    }

    if (code_type == 0x9) {
        uint8_t X = code_content / 0x100;
        uint8_t Y = (code_content % 0x100) / 0x10 ;

        uint8_t x = readRegister(X);
        uint8_t y = readRegister(Y);
        if (x != y) incrementPC();

        return;
    }

    if (code_type == 0xA) {
        setIndex(code_content);
        return;
    }

    if (code_type == 0xB) {

    }

    if (code_type == 0xC) {

    }

    if (code_type == 0xD) {
        uint8_t X, Y, N;
        X = code_content / 0x100;
        Y = (code_content % 0x100) / 0x10;
        N = (code_content % 0x10);

        uint8_t x = readRegister(X);
        uint8_t y = readRegister(Y);

        drawSprite(x, y, N);
        displayEdit();
        return;
    }

    if (code_type == 0xE) {

    }

    if (code_type == 0xF) {

    }

}
