#pragma once

#include <cstdint>


void setPC(uint16_t addr);

uint16_t readPC();

void incrementPC();

void decrementPC();


void stackPC(uint16_t call);

void returnPC();


void setRegister(uint8_t vx, uint8_t content);

uint8_t addToRegister(uint8_t vx, uint8_t content);

uint8_t readRegister(uint8_t vx);


void setIndex(uint16_t content);

bool addToIndex(uint8_t content);

uint16_t readIndex();

void updateIndexUpdate(int X);
