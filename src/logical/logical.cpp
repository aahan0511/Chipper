#include "logical.hpp"
#include "../cpu/cpu.hpp"
#include "../execute/execute.hpp"

#include <cstdint>


void op0(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    setRegister(X, y);
}


void op1(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    setRegister(X, x | y);
}

void op2(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    setRegister(X, x & y);
}

void op3(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    setRegister(X, x ^ y);
}


void op4(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    uint16_t sum = x + y;
    setRegister(X, sum);

    if (sum > 0xFF) {
        setRegister(0xF, 1);
    } else {
        setRegister(0xF, 0);
    }
}

void op5(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    int difference = x - y;
    setRegister(X, difference);

    if (difference >= 0) {
        setRegister(0xF, 1);
    } else {
        setRegister(0xF, 0);
    }
}

void op7(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    int difference = y - x;
    setRegister(X, difference);

    if (difference >= 0) {
        setRegister(0xF, 1);
    } else {
        setRegister(0xF, 0);
    }
}


void op6(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    if (AMBIGUITY_SHIFT) {          // ORIGINAL
        setRegister(X, y >> 1);
        setRegister(0xF, y % 2);
    } else {                        // NEW
        setRegister(X, x >> 1);
        setRegister(0xF, x % 2);
    }
}

void opE(
    uint16_t X, uint16_t Y,
    uint8_t x, uint8_t y
) {
    if (AMBIGUITY_SHIFT) {                  // ORIGINAL
        setRegister(X, y << 1);
        setRegister(0xF, y / 0b10000000);
    } else {                                // NEW
        setRegister(X, x << 1);
        setRegister(0xF, x / 0b10000000);
    }
}
