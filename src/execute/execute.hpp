#pragma once

#include <cstdint>


void addCall(uint16_t call);

uint16_t popCall();


// false -> uses the new convention for commands with ambiguous instructions
// true -> uses the original chip-8 convention with ambiguous instructions
inline bool AMBIGUITY = false;

void execute();
