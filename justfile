set positional-arguments

build_dir := "build"
build_type := "Release"

default:
    @just --list

# Configure (fast no-op when already configured)
configure:
    cmake -B {{build_dir}} -DCMAKE_BUILD_TYPE={{build_type}}

# Incremental build
build: configure
    cmake --build {{build_dir}} --parallel --target Chipper

# Build, then run. Usage: just run path/to/rom.ch8
run *args: build
    ./{{build_dir}}/Chipper "$@"

# Full rebuild of your code
rebuild:
    cmake --build {{build_dir}} --target clean
    @just build

# Delete the build dir (re-fetches raylib next time)
reset:
    rm -rf {{build_dir}}

# Run the test ROMs one after another. Usage: just test ~/chip8-test-suite
test suite: build
    #!/usr/bin/env bash
    set -eu
    roms=(
      "1-chip8-logo|CHIP-8 splash screen"
      "2-ibm-logo|IBM logo"
      "3-corax+|Corax+ opcode test"
      "4-flags|Flags test"
      "5-quirks|Quirks test"
      "6-keypad|Keypad test"
      "7-beep|Beep test"
    )
    for entry in "${roms[@]}"; do
      ./{{build_dir}}/Chipper "{{suite}}/bin/${entry%%|*}.ch8" "${entry#*|}"
    done
