// Lines marked with `// *` are AI-generated

#include "cli.hpp"

#include "../runtime/runtime.hpp"

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
    std::cout << std::endl;

    int width = getTerminalWidth();
    for (int _ = 0; _ < width; _++) {
        std::cout << symbol;
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

void sprtrWithText(std::string text, char symbol) {
    if (getTerminalWidth() <= text.size()) {
        drawSprtr(symbol);
        return;
    }

    std::cout << std::endl;

    int t_width = getTerminalWidth();
    int text_width = 1 + text.size() + 1;
    int width = (t_width - text_width) / 2;

    for (int _ = 0; _ < width; _++)
        std::cout << symbol;
    std::cout << " " << text << " ";
    for (int _ = 0; _ < width; _++)
        std::cout << symbol;

    if (2 * width + text_width < t_width)
        std::cout << symbol;

    std::cout << std::endl;
    std::cout << std::endl;
}


void error(std::string message, std::string symbol) {
    std::cout << symbol << ": " << message << std::endl;

    sprtrWithText("END");
    if (checkInit())
        deinit();
    exit(EXIT_FAILURE);
}

void warning(std::string message, std::string symbol) {
    std::cout << symbol << ": " << message << std::endl;
}

void info(std::string message, std::string symbol) {
    std::cout << symbol << ": " << message << std::endl;
}

void debug(std::string message, std::string symbol) {
    std::cout << symbol << ": " << message << std::endl;
}
