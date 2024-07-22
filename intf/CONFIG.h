// Game Configuration

#pragma once // Include only once

#define TITLE "CWORDLE"
#define TITLE_COLOR ANSI_COLOR_GREEN
#define WORD_SIZE 6                          // how long each word is (+1 for null terminator)
#define MAX_WORDS 14855                      // the amount of words (lines) in the file
#define MAX_LENGTH (MAX_WORDS * WORD_SIZE)   // the length of the words file (linecount * charcount)
#define NUM_GUESSES 6                        // the max amount of guesses the player can do

// the file has to be a text file where each line is a word with constant length
// if you want to include a custom words file, also change the following definitions
// WORD_SIZE: how long each word (line) is
// MAX_WORDS: the line count of the file
#define WORDS_FILE_PATH "words.txt"          // the words file relative to main.c