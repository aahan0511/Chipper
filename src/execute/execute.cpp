#include "execute.hpp"

#include "../cli/cli.hpp"
#include "../cpu/cpu.hpp"
#include "../display/display.hpp"
#include "../draw/draw.hpp"
#include "../font/font.hpp"
#include "../keypad/keypad.hpp"
#include "../logical/logical.hpp"
#include "../memory/memory.hpp"
#include "../quirks/quirks.hpp"
#include "../random/random.hpp"
#include "../timer/timer.hpp"

#include <cstdint>
#include <format>
#include <stack>
#include <string>


constexpr uint8_t call_stack_depth = 0x10;

std::stack<uint16_t> call_stack;

void addCall(uint16_t call) {
    if (call_stack.size() == call_stack_depth)
        error("call stack full");

    call_stack.push(call);
}

uint16_t popCall() {
    if (call_stack.size() == 0)
        error("call stack empty");

    uint16_t call = call_stack.top();
    call_stack.pop();

    return call;
}


bool warned_0 = false;
bool warned_8 = false;
bool warned_E = false;
bool warned_F = false;

void execute() {
    uint16_t opcode = readPC();
    incrementPC();

    uint16_t code_type = opcode / 0x1000;
    uint16_t code_content = opcode % 0x1000;

    switch (code_type) {
        case 0x0: {
            if (opcode == 0x00E0) {
                clearDisplay();
            } else if (opcode == 0x00EE) {
                returnPC();
            } else {
                if (!(warned_0)) {
                    warning("opcode 0x" + std::format("{:04X}", opcode) + " is ignored");
                    warned_0 = true;
                }
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
                default: {
                    if (!(warned_8)) {
                        warning("unknown opcode 0x" + std::format("{:04X}", opcode) + " used");
                        warned_8 = true;
                    }
                    break;
                }
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
            if (checkQuirk("jump")) {
                uint8_t X = code_content / 0x100;
                uint8_t x = readRegister(X);

                setPC(code_content + x);
            } else {
                uint8_t v0 = readRegister(0);

                setPC(code_content + v0);
            }
            break;
        }
        case 0xC: {
            uint8_t X = code_content / 0x100;
            uint8_t NN = code_content % 0x100;

            uint8_t random_n = generateRandom();

            setRegister(X, random_n & NN);

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
            uint8_t X = code_content / 0x100;
            uint8_t type = code_content % 0x100;

            uint8_t x = readRegister(X);

            if (type == 0x9E) {
                if (isKeyDown(x))
                    incrementPC();
            } else if (type == 0xA1) {
                if (isKeyUp(x))
                    incrementPC();
            } else {
                if (!(warned_E)) {
                    warning("unknown opcode 0x" + std::format("{:04X}", opcode) + " used");
                    warned_E = true;
                }
            }

            break;
        }
        case 0xF: {
            uint8_t X = code_content / 0x100;
            uint8_t x = readRegister(X);
            uint8_t type = code_content % 0x100;
            uint16_t I = readIndex();

            switch (type) {
                case (0x1E): {
                    if (checkQuirk("addIndexLeaveFUnchanged")) {
                        addToIndex(x);
                    } else {
                        bool overflowed = addToIndex(x);
                        if (overflowed) setRegister(0xF, 1);
                        else setRegister(0xF, 0);
                    }

                    break;
                }
                case (0x33): {
                    setMemory(I, x / 100);
                    setMemory(I + 1, (x % 100) / 10);
                    setMemory(I + 2, x % 10);

                    break;
                }
                case (0x55): {
                    for (int i = I; i <= X + I; i++)
                        setMemory(i, readRegister(i - I));

                    updateIndexUpdate(X);

                    break;
                }
                case (0x65): {
                    for (int i = I; i <= X + I; i++)
                        setRegister(i - I, readMemory(i));

                    updateIndexUpdate(X);

                    break;
                }
                case (0x0A): {
                    uint8_t pressed_key = anyKeyPressed();
                    if (pressed_key == (uint8_t)(-1)) {
                        decrementPC();
                    } else {
                        setRegister(X, pressed_key);
                    }

                    break;
                }
                case (0x07): {
                    setRegister(X, readDelayTimer());

                    break;
                }
                case (0x15): {
                    setDelayTimer(x);

                    break;
                }
                case (0x18): {
                    setSoundTimer(x);

                    break;
                }
                case (0x29): {
                    setIndex(getFontAddr(x));

                    break;
                }
                default: {
                    if (!(warned_F)) {
                        warning("unknown opcode 0x" + std::format("{:04X}", opcode) + " used");
                        warned_F = true;
                    }

                    break;
                }
            }

            break;
        }
    }
}
