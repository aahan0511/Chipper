run *args="":
    cmake --build build
    ./build/Chipper {{args}}

run-with-build *args="":
    cmake -B build
    cmake --build build
    ./build/Chipper {{args}}

build:
    cmake -B build

compile:
    cmake --build build

execute:
    ./build/Chipper
