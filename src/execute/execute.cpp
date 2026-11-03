#include "execute.hpp"
#include "../display/display.hpp"
#include "../cpu/cpu.hpp"
#include "../draw/draw.hpp"
#include "../cli/cli.hpp"
#include "../logical/logical.hpp"
#include "../random/random.hpp"
#include "../memory/memory.hpp"
#include "../keypad/keypad.hpp"
#include "../timer/timer.hpp"
#include "../font/font.hpp"

#include <cstdint>
#include <stack>


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
            if (AMBIGUITY_JUMP_OFFSET) {            // ORIGINAL
                uint8_t v0 = readRegister(0);

                setPC(code_content + v0);
            } else {                                // NEW
                uint8_t X = code_content / 0x100;
                uint8_t x = readRegister(X);

                setPC(code_content + x);
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
                    if (AMBIGUITY_ADD_INDEX) {                  // ORIGINAL
                        addToIndex(x);
                    } else {                                    // AMIGA
                        bool overflowed = addToIndex(x);
                        if (overflowed) setRegister(0xF, 1);
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
                    if (AMBIGUITY_LOAD_REGISTER) {                                  // ORIGINAL
                        for (; readIndex() <= X + I; addToIndex(1))
                            setMemory(readIndex(), readRegister(readIndex() - I));
                    } else {                                                        // NEW
                        for (int i = I; i <= X + I; i++)
                            setMemory(i, readRegister(i - I));
                    }

                    break;
                }
                case (0x65): {
                    if (AMBIGUITY_LOAD_REGISTER) {                                  // ORIGINAL
                        for (; readIndex() <= X + I; addToIndex(1))
                            setRegister(readIndex() - I, readMemory(readIndex()));
                    } else {                                                        // NEW
                        for (int i = I; i <= X + I; i++)
                            setRegister(i - I, readMemory(i));
                    }

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
            }

            break;
        }
    }
}
