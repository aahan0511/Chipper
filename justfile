run *args="":
    cmake --build build
    ./build/Chipper {{args}}

run-with-build *args="":
    cmake -B build
    cmake --build build
    ./build/Chipper {{args}}


test chip8_test_suite_path:
    cmake --build build
    ./build/Chipper {{chip8_test_suite_path}}/bin/1-chip8-logo.ch8 "CHIP-8 splash screen"
    ./build/Chipper {{chip8_test_suite_path}}/bin/2-ibm-logo.ch8 "IBM logo"
    ./build/Chipper {{chip8_test_suite_path}}/bin/3-corax+.ch8 "Corax+ opcode test"
    ./build/Chipper {{chip8_test_suite_path}}/bin/4-flags.ch8 "Flags test"
    ./build/Chipper {{chip8_test_suite_path}}/bin/5-quirks.ch8 "Quirks test"
    ./build/Chipper {{chip8_test_suite_path}}/bin/6-keypad.ch8 "Keypad test"
    ./build/Chipper {{chip8_test_suite_path}}/bin/7-beep.ch8 Beep test""



build *args="":
    cmake -B build {{args}}

compile *args="":
    cmake --build build {{args}}

execute *args="":
    ./build/Chipper {{args}}
