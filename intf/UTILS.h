// Includes

#pragma once // Include only once

// include some header files
#include <stdio.h>    // for input/output
#include <string.h>   // for string comparison
#include <stdbool.h>  // for boolean types
#include <ctype.h>    // for isspace(char) function
#include <time.h>     // for random seed in srand
#include <stdlib.h>   // for rand function
#include "CONFIG.h"   // for WORD_SIZE

// define csleep function based on OS
#ifdef _WIN32
#include <windows.h>
void csleep(unsigned int milliseconds) {
    Sleep(milliseconds);
}
#elif __unix__
#include <unistd.h>
void csleep(unsigned int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
#else
#error "Unsupported platform"
#endif

// checks if string contains a character
bool strcontains(char word[WORD_SIZE], char c) {
    for(int i = 0; i < WORD_SIZE; i++) if(word[i] == c) return true;
    return false;
}