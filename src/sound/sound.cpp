// Lines marked with `// *` are AI-generated

#include "sound.hpp"

#include "raylib.h"

#include <cmath>
#include <cstdint>
#include <vector>


Sound makeBeep(float freq, float seconds, float volume = 0.4f) {    // *
    const unsigned rate = 44100;                                    // *
    const unsigned frames = static_cast<unsigned>(rate * seconds);  // *
    std::vector<int16_t> samples(frames);                           // *

    for (unsigned i = 0; i < frames; ++i) {     // *
        float t = static_cast<float>(i) / rate; // *
    float env = std::fmin(1.0f, std::fmin(i, frames - i) / (rate * 0.005f));                    // *
        samples[i] = static_cast<int16_t>(32767 * volume * env * std::sin(2 * PI * freq * t));  // *
    }

    Wave w{};                       // *
    w.frameCount = frames;          // *
    w.sampleRate = rate;            // *
    w.sampleSize = 16;              // *
    w.channels   = 1;               // *
    w.data       = samples.data();  // *

    return LoadSoundFromWave(w);    // *
}


Sound beep;

void playSound() {
    if (IsSoundPlaying(beep)) return;
    PlaySound(beep);
}

void stopSound() {
    if (IsSoundPlaying(beep))
        StopSound(beep);
}


void initAudio() {
    InitAudioDevice();
    beep = makeBeep(880.0f, 0.2f);    // *
}

void closeAudio() {
    UnloadSound(beep);
    CloseAudioDevice();
}
