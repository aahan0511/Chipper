// Lines marked with `// *` are AI-generated

#include "cli.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

#ifdef _WIN32            // *
  #include <windows.h>   // *
#else                    // *
  #include <sys/ioctl.h> // *
  #include <unistd.h>    // *
#endif                   // *


int getTerminalWidth() {
    #ifdef _WIN32                                                               // *
        CONSOLE_SCREEN_BUFFER_INFO csbi;                                        // *
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) // *
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;                // *
    #else                                                                       // *
        winsize w;                                                              // *
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0)          // *
            return w.ws_col;                                                    // *
    #endif                                                                      // *
                                                                                // *
    return 80;                                                                  // *
}

void drawSprtr(char symbol) {
    std::cout << "\n";

    int width = getTerminalWidth();
    for (int _ = 0; _ < width; _++) {
        std::cout << symbol;
    }

    std::cout << "\n";
    std::cout << "\n";
}

void sprtrWithText(std::string text, char symbol) {
    std::cout << "\n";

    int width = (getTerminalWidth() - text.size()) / 2;
    for (int _ = 0; _ < width; _++) {
        std::cout << symbol;
    }
    std::cout << text;
    for (int _ = 0; _ < width; _++) {
        std::cout << symbol;
    }

    std::cout << "\n";
    std::cout << "\n";
}

void error(std::string message) {
    std::cout << ERROR << ": " << message << "\n";

    sprtrWithText("END");
    exit(EXIT_FAILURE);
}

void warning(std::string message) {
    std::cout << WARNING << ": " << message << "\n";
}

void info(std::string message) {
    std::cout << INFO << ": " << message << "\n";
}
