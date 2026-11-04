#include "timer.hpp"

#include <chrono>
#include <cstdint>


 std::chrono::time_point delay_timer_time = std::chrono::steady_clock::now();
 uint8_t delay_timer = 0;

void setDelayTimer(uint8_t content) {
    delay_timer_time = std::chrono::steady_clock::now();
    delay_timer = content;
}

uint8_t readDelayTimer() {
    int elapsed = (double)(std::chrono::duration<double>(std::chrono::steady_clock::now() - delay_timer_time).count()) * FREQ;

    if (elapsed >= delay_timer) {
        return 0;
    } else {
        return delay_timer - elapsed;
    }
}


std::chrono::time_point sound_timer_time = std::chrono::steady_clock::now();
uint8_t sound_timer = 0;

void setSoundTimer(uint8_t content) {
   sound_timer_time = std::chrono::steady_clock::now();
   sound_timer = content;
}

bool checkSoundTimer() {
    int elapsed = (double)(std::chrono::duration<double>(std::chrono::steady_clock::now() - sound_timer_time).count()) * FREQ;

    if (elapsed >= sound_timer) {
        return false;
    } else {
        return true;
    }
}
