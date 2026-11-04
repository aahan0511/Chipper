#pragma once

#include <string>


bool checkQuirk(std::string quirk);

void loadQuirks(
    bool shift = false,
    bool memoryLeaveIUnchanged = false,
    bool memoryIncrementByX = false,
    bool wrap = false,
    bool jump = false,
    bool vblank = true,
    bool logic = true,

    bool addIndexLeaveFUnchanged = true
);
