#include "execute.hpp"
#include "../display/display.hpp"
#include "../cpu/cpu.hpp"
#include "../draw/draw.hpp"
#include "../cli/cli.hpp"
#include "../logical/logical.hpp"

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

    switch (code_type) {
        case 0x0: {
            if (opcode == 0x00E0) {
                clearDisplay();
                displayEdit();
            }

            if (opcode == 0x00EE) {
                returnPC();
            }

            break;
        }
        case 0x1: {
            setPC(code_content);

            break;
        }
        case 0x2: {
            stackPC(code_content);

            break;
        }
        case 0x3: {
            uint8_t X = code_content / 0x100;
            uint8_t NN = code_content % 0x100;

            uint8_t x = readRegister(X);
            if (x == NN) incrementPC();

            break;
        }
        case 0x4: {
            uint8_t X = code_content / 0x100;
            uint8_t NN = code_content % 0x100;

            uint8_t x = readRegister(X);
            if (x != NN) incrementPC();

            break;
        }
        case 0x5: {
            uint8_t X = code_content / 0x100;
            uint8_t Y = (code_content % 0x100) / 0x10 ;

            uint8_t x = readRegister(X);
            uint8_t y = readRegister(Y);
            if (x == y) incrementPC();

            break;
        }
        case 0x6: {
            uint16_t vx = code_content / 0x100;
            uint16_t content = code_content % 0x100;

            setRegister(vx, content);

            break;
        }
        case 0x7: {
            uint16_t vx = code_content / 0x100;
            uint16_t content = code_content % 0x100;

            addToRegister(vx, content);

            break;
        }
        case 0x8: {
            uint16_t X = code_content / 0x100;
            uint16_t Y = (code_content % 0x100) / 0x10;
            uint16_t operation = code_content % 0x10;

            uint8_t x = readRegister(X);
            uint8_t y = readRegister(Y);

            switch (operation) {
                case 0x0:
                    op0(X, Y, x, y);
                    break;
                case 0x1:
                    op1(X, Y, x, y);
                    break;
                case 0x2:
                    op2(X, Y, x, y);
                    break;
                case 0x3:
                    op3(X, Y, x, y);
                    break;
                case 0x4:
                    op4(X, Y, x, y);
                    break;
                case 0x5:
                    op5(X, Y, x, y);
                    break;
                case 0x7:
                    op7(X, Y, x, y);
                    break;
                case 0x6:
                    op6(X, Y, x, y);
                    break;
                case 0xE:
                    opE(X, Y, x, y);
                    break;
            }

            break;
        }
        case 0x9: {
            uint8_t X = code_content / 0x100;
            uint8_t Y = (code_content % 0x100) / 0x10 ;

            uint8_t x = readRegister(X);
            uint8_t y = readRegister(Y);
            if (x != y) incrementPC();

            break;
        }
        case 0xA: {
            setIndex(code_content);

            break;
        }
        case 0xB: {
            if (AMBIGUITY) {    // OLD
                uint8_t v0 = readRegister(0);

                setPC(code_content + v0);
            } else {            // NEW
                uint8_t X = code_content / 0x100;
                uint8_t x = readRegister(X);

                setPC(code_content + x);
            }
            break;
        }
        case 0xC: {
            break;
        }
        case 0xD: {
            uint8_t X, Y, N;
            X = code_content / 0x100;
            Y = (code_content % 0x100) / 0x10;
            N = (code_content % 0x10);

            uint8_t x = readRegister(X);
            uint8_t y = readRegister(Y);

            drawSprite(x, y, N);
            displayEdit();

            break;
        }
        case 0xE: {
            break;
        }
        case 0xF: {
            break;
        }
    }
}
