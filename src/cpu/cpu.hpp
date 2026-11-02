#pragma once

#include <cstdint>


uint16_t setPC(int addr);

uint16_t readPC();

uint16_t incrementPC();


void setRegister(int vx, uint8_t content);

uint8_t addToRegister(int vx, uint8_t content);

uint8_t readRegister(int vx);


void setIndex(uint16_t content);

uint16_t readIndex();
