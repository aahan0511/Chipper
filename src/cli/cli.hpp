#pragma once

#include <string>


constexpr std::string ERROR = "FATAL";
constexpr std::string WARNING = "WARNING";
constexpr std::string INFO = "INFO";

void drawSprtr(char symbol = '-');

void sprtrWithText(std::string text, char symbol = '=');

void error(std::string message);

void warning(std::string message);

void info(std::string message);
