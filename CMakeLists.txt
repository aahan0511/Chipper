cmake_minimum_required(VERSION 3.20)
project(Chipper CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 6.0
  GIT_SHALLOW TRUE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(Chipper
  main.cpp
  src/display/display.cpp
  src/memory/memory.cpp
  src/font/font.cpp
  src/cli/cli.cpp
)
target_link_libraries(Chipper PRIVATE raylib)
