run *args="":
    cmake --build build
    ./build/Chipper {{args}}

run-with-build *args="":
    cmake -B build
    cmake --build build
    ./build/Chipper {{args}}

build *args="":
    cmake -B build {{args}}

compile *args="":
    cmake --build build {{args}}

execute *args="":
    ./build/Chipper {{args}}
