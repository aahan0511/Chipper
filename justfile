run:
    cmake --build build
    ./build/Chipper

run-with-build:
    cmake -B build
    cmake --build build
    ./build/Chipper

build:
    cmake -B build

compile:
    cmake --build build

execute:
    ./build/Chipper
