# CHIP-8 Emulator

This project is a CHIP-8 emulator for [Hack Club's Chipper](https://chipper.hackclub.com/) written in C++ and raylib.
The emulator implements the base CHIP-8 instructions with quirks aligned to the original COSMIC VIP.

## Running

You can change the settings and quirks inside `./settings.hpp`.

### Quick start

If you have [`just`](https://github.com/casey/just):
```bash
just run <file>
```
This configures, builds (incrementally) and runs the emulator in one step. On a fresh clone the first build also fetches and compiles raylib, so it takes a bit longer.

Without `just`:
```bash
cmake -B build
cmake --build build --parallel
./build/Chipper <file>
```

Builds default to `Release`. To override that, pass `-DCMAKE_BUILD_TYPE=Debug` to the configure step.

### Other `just` commands

| Command | What it does |
| --- | --- |
| `just` | Lists all available commands |
| `just configure` | Runs the CMake configure step |
| `just build` | Configures if needed, then builds incrementally |
| `just run <file>` | Builds if needed, then runs the emulator with `<file>` |
| `just rebuild` | Cleans the Chipper target and builds it again |
| `just reset` | Deletes `build/` (raylib is fetched again on the next build) |
| `just test <chip8-test-suite directory>` | Builds, then runs tests 1 to 7 of the [CHIP-8 Test Suite](https://github.com/Timendus/chip8-test-suite) one by one |

For a debug build in its own directory:
```bash
just build_type=Debug build_dir=build-debug run <file>
```

## Credits

Most of my work is based on [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/) by [Tobias V. I. Langhoff](https://github.com/tobiasvl), he really has written an amazing guide.

And without [Timendus' CHIP-8 test suite](https://github.com/Timendus/chip8-test-suite), I would not have been able to work out any of the bugs and quirks.

Huge thanks to both of them!
