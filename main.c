// CWORDLE
// Wordle in C
// Written by Vardan Petrosyan 22/07/2024

#include "intf/ANSI.h"   // ansi color codes
#include "intf/CONFIG.h" // game configuration
#include "intf/UTILS.h"   // utilities
#include "intf/DEFS.h"   // structure definitions

// all words read from file
char words[MAX_LENGTH][WORD_SIZE];

// the pointer to the words file
FILE *wordsptr;

// the guesses made by the player
GuessChar guesses[NUM_GUESSES][WORD_SIZE];

// function to read the words from the path
bool readWords() {
    int idx = 0;
    // open the file with path
    wordsptr = fopen(WORDS_FILE_PATH,"r");

    // if the pointer points to NULL, the file reading failed
    if(wordsptr == NULL) {
        perror("Error opening file"); //print error
        return false; // return false as in not successful
    }

    // variable to store current word
    char currentword[WORD_SIZE];

    // while there are lines to read
    while(fgets(currentword, WORD_SIZE, wordsptr)) {
        if(idx >= MAX_LENGTH) {
            fprintf(stderr, "Exceeded maximum number of words\n");
            fclose(wordsptr); // close file
            return false;     // return false as in not successful
        }
        // if the line is just whitespace, ignore
        if(isspace(currentword[0])) continue;

        // add to words and increment index
        strcpy(words[idx], currentword);
        idx++;
    }
    
    // return true as in successful
    return true;
}

// print the guesses of the player
// args: 
//    int guess - guess no.
void printGame(int guess) {
    // clears the screen
    clearScreen();

    // print title
    printf(TITLE_COLOR);
    printf(TITLE);
    printf(ANSI_COLOR_RESET);
    printf("\n\n");

    // for each guess
    for(int pg = 0; pg < guess; pg++) // print the guesses up to the current one
    {
        // for each character in that guess
        printf("%d. ", pg + 1);
        for(int pc = 0; pc < WORD_SIZE; pc++)
        {
            // determine the color of the guess
            char *color;
            switch (guesses[pg][pc].t) // switch though the CharType of the character
            {
                case CORRECT:
                    color = ANSI_COLOR_GREEN; // Green for Correct
                    break;
                case CONTAINS:
                    color = ANSI_COLOR_YELLOW; // Yellow for Contains
                    break;
                case NONE:
                default:
                    color = ANSI_COLOR_RED;   // Red for None
                    break;
            }
            printf(color); // print the color ANSI
            printf("%c", guesses[pg][pc].c); // print the character
            printf(ANSI_COLOR_RESET); // reset the color
            if(pg == guess - 1) // if last one
                csleep(100);
        }
        printf("\n"); // print a newline after printing the guess
    }
}

// Function to count occurrences of each character in the word
void count_chars(char *word, int *counts) {
    for (int i = 0; i < WORD_SIZE; i++) {
        counts[word[i] - 'a']++;
    }
}

void process_guess(char *word, char *input, int guess) {
    int counts[26] = {0}; // Assuming only lowercase letters 'a' to 'z'
    bool marked[WORD_SIZE] = {false}; // To mark already processed characters

    // First pass: Mark all correct positions
    for (int i = 0; i < WORD_SIZE; i++) {
        if (input[i] == word[i]) {
            guesses[guess][i] = (GuessChar){input[i], CORRECT};
            marked[i] = true;
        } else {
            guesses[guess][i] = (GuessChar){input[i], NONE};
        }
    }

    // Count remaining occurrences of each character in the word
    count_chars(word, counts);
    for (int i = 0; i < WORD_SIZE; i++) {
        if (input[i] == word[i]) {
            counts[word[i] - 'a']--; // Decrement count for correct matches
        }
    }

    // Second pass: Mark contains positions
    for (int i = 0; i < WORD_SIZE; i++) {
        if (!marked[i] && strcontains(word, input[i]) && counts[input[i] - 'a'] > 0) {
            guesses[guess][i].t = CONTAINS;
            counts[input[i] - 'a']--; // Decrement count for contain matches
        }
    }
}

int main() {
    srand(time(NULL)); // set random seed based on time
    if(!readWords()) return 1; // if failed to read words, return with error
    char word[WORD_SIZE];

    // get a random word and copy it to `word`
    strcpy(word, words[rand() % (MAX_WORDS - 1)]);

    printGame(0); // print the game initially

    for (int guess = 0; guess < NUM_GUESSES; guess++){
        char input[WORD_SIZE];

        while(true) {
            printf("%d. ", guess + 1);
            scanf("%s", &input);
            if(strlen(input) + 1 != WORD_SIZE) // if the length of input (+1 for null terminator) is not equal to the size
                printf("Not right size!\n");
            else
                break; // if the input is correct, break out of loop
        }

        process_guess(word, input, guess);

        printGame(guess + 1); // print the game table

        // if the guess is correct
        if(strcmp(input,word) == 0) 
            break; // exit the loop early
    }

    // at the end of the game, print the correct word
    printf("The word was ");
    printf(ANSI_COLOR_GREEN);
    printf(word);
    printf(ANSI_COLOR_RESET);

    return 0; // return with success
}