#pragma once

#include <string>


void drawSprtr(char symbol = '-');

void sprtrWithText(std::string text, char symbol = '=');


constexpr std::string ERROR = "FATAL";
constexpr std::string WARNING = "WARNING";
constexpr std::string INFO = "INFO";

void error(std::string message, std::string symbol = ERROR);

void warning(std::string message, std::string symbol = WARNING);

void info(std::string message, std::string symbol = INFO);
