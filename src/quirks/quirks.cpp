#include "quirks.hpp"

#include "../cli/cli.hpp"

#include <string>
#include <unordered_map>


std::unordered_map<std::string, bool> quirks = {
    {"shift", false},
    {"memoryIncrementByX", false},
    {"memoryLeaveIUnchanged", false},
    {"wrap", false},
    {"jump", false},
    {"vblank", true},
    {"logic", true},

    {"addIndexLeaveFUnchanged", true},
};

bool checkQuirk(std::string quirk) {
    if (quirks.contains(quirk))
        return quirks[quirk];

    error("undefined quirk");
    return false;
}


void loadQuirks(
    bool shift,
    bool memoryLeaveIUnchanged,
    bool memoryIncrementByX,
    bool wrap,
    bool jump,
    bool vblank,
    bool logic,

    bool addIndexLeaveFUnchanged
) {
    quirks["shift"] = shift;
    quirks["memoryLeaveIUnchanged"] = memoryLeaveIUnchanged;
    quirks["memoryIncrementByX"] = memoryIncrementByX;
    quirks["wrap"] = wrap;
    quirks["jump"] = jump;
    quirks["vblank"] = vblank;
    quirks["logic"] = logic;

    quirks["addIndexLeaveFUnchanged"] = addIndexLeaveFUnchanged;
}
