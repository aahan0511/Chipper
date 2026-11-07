#pragma once

#include "../../settings.hpp"

#include <cstdlib>
#include <string>


void drawSprtr(char symbol = '-');

void sprtrWithText(std::string text, char symbol = '=');


void error(std::string message, std::string symbol = CLI_ERROR);

void warning(std::string message, std::string symbol = CLI_WARNING);

void info(std::string message, std::string symbol = CLI_INFO);

void debug(std::string message, std::string symbol = CLI_DEBUG);


void setFileLabel(std::string label);

std::string getFileLabel();


void stop(int status = EXIT_SUCCESS);
