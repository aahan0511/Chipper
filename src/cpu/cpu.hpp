#pragma once

#include <cstdint>


uint16_t setPC(uint16_t addr);

uint16_t readPC();

uint16_t incrementPC();


void stackPC(uint16_t call);

void returnPC();


void setRegister(uint8_t vx, uint8_t content);

uint8_t addToRegister(uint8_t vx, uint8_t content);

uint8_t readRegister(uint8_t vx);


void setIndex(uint16_t content);

bool addToIndex(uint8_t content);

uint16_t readIndex();
