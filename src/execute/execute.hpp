#pragma once

#include <cstdint>


void addCall(uint16_t call);

uint16_t popCall();


// true -> uses the original chip-8 convention with ambiguous instructions
// false -> uses the new convention for commands with ambiguous instructions
inline bool AMBIGUITY_SHIFT = false;
inline bool AMBIGUITY_JUMP_OFFSET = false;
inline bool AMBIGUITY_LOAD_REGISTER = false;

// true -> uses the original chip-8 convention with ambiguous instructions
// false -> uses the Amiga convention with ambiguous instructions
inline bool AMBIGUITY_ADD_INDEX = false;


void execute();
