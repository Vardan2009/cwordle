// Structure Definitions

#pragma once // Include only once

// The type of letter (character) in each guess
// CORRECT:  the letter is correctly placed
// CONTAINS: the letter is in the word but wrongly placed
// NONE:     the letter is not in the word
typedef enum CharType {
    CORRECT, CONTAINS, NONE
} CharType;

// Structure for each character in the guess
// c:  the character
// t:  the type (refer to CharType above)
typedef struct GuessChar {
    char c;
    CharType t;
} GuessChar;