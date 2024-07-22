// ANSI Color Codes
// WIll only work on terminals that support ANSI

#pragma once // Include only once

#include <stdio.h>

// Color definitions
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// definition for clearScreen in ANSI.h
void clearScreen() {
  printf("\e[1;1H\e[2J");
}