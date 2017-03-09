/**
 * Exercise 7-5
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number conversion. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


#define MAX_DEPTH 100           // max stack depth

typedef enum State {
    BLANK,                      // parse next token from stream
    SEEKING_NUMBER_WO_PM,       // parse number from stream
    SEEKING_NEG_NUMBER_WO_PM,   // parse number from stream and negate
    EXIT                        // finished
} State;

long stack[MAX_DEPTH];
int stackPosition;

int peek(char* nextChar);       // peek at the next char in stream, without changing position
State doBlank();                // parse next token, or begin parsing next token
State doSeekingNumberWoPM();    // parse an integer and push to stack
State doSeekingNegNumberWoPM(); // parse an integer, negate, and then push to stack
State add();                    // perform add operation on stack, return next state 
State subtract();               // perform subtract operation on stack, return next state
State multiply();               // perform multiply operation on stack, return next state
State divide();                 // perform divide operation on stack, return next state

int main (int argc, char* argv[]) {
    State state = BLANK;

    stackPosition = 0;
    printf("Exercise 7-5 Polish Calculator\n");
    printf("Operations supported: + - / * (separated by whitespace)\n");
    printf("Maximum stack depth: %d\n", MAX_DEPTH);
    printf("Usage example: for operations (0 + 1) * 5, enter \"0 1 + 5 *\"\n");
    printf("\nBegin:\n");
    while (true) {
        switch (state) {
            case BLANK:
                state = doBlank();
                break;
            case SEEKING_NUMBER_WO_PM:
                state = doSeekingNumberWoPM();
                break;
            case SEEKING_NEG_NUMBER_WO_PM:
                state = doSeekingNegNumberWoPM();
                break;
            case EXIT:
                break;
            default:
                printf("State error.\n");
                state = EXIT;
                break;
        }
        if (state == EXIT) break;
    }
    printf("Ending.\n");
    return EXIT_SUCCESS;
}

// peek at the next char in stream, without changing position
int peek(char* nextChar) {
    int result = scanf("%c", nextChar);
    if (result != EOF && result > 0) {
        ungetc(*nextChar, stdin);
    } else if (result == 0) {
        printf("scanf error: failed to read char.\n");
    }
    return result;
}

// parse next token, or begin parsing next token
State doBlank() {
    char char0, char1;
    int result;

    result = scanf("%c", &char0);
    if (result == EOF) {
        return EXIT;
    } else if (result == 0) {
        printf("scanf error: failed to read char.\n");
        return EXIT;
    } else if (char0 == '+' || char0 == '-') {
        result = peek(&char1);
        if (result == EOF) {
            (char0 == '+') ? add() : subtract();
            return EXIT;
        } else if (result == 0) {
            (char0 == '+') ? add() : subtract();
            return EXIT;
        } else if (isdigit(char1)) {
            return (char0 == '+') ? SEEKING_NUMBER_WO_PM : SEEKING_NEG_NUMBER_WO_PM;
        } else {
            return (char0 == '+') ? add() : subtract();
        }
    } else if (isdigit(char0)) {
        ungetc(char0, stdin);
        return SEEKING_NUMBER_WO_PM;
    } else if (char0 == '*' || char0 == '/') {
        return (char0 == '*') ? multiply() : divide();
    } else if (isspace(char0)) {
        return BLANK;
    } else {
        printf("error: invalid char %c\n", char0);
        return EXIT;
    }
    printf("error in BLANK state.\n"); 
    return EXIT;
}

// parse an integer and push to stack
State doSeekingNumberWoPM() {
    long number;
    scanf("%ld", &number);
    if (stackPosition < MAX_DEPTH) {
        stack[stackPosition++] = number;
        return BLANK;
    } else {
        printf("Stack capacity exceeded.\n");
        return EXIT;
    }
    printf("error in SEEKING_NUBMER_WO_PM state.\n"); 
    return EXIT;
}

// parse an integer, negate, and then push to stack
State doSeekingNegNumberWoPM() {
    long number;
    scanf("%ld", &number);
    if (stackPosition < MAX_DEPTH) {
        stack[stackPosition++] = -number;
        return BLANK;
    } else {
        printf("Stack capacity exceeded.\n");
        return EXIT;
    }
}

// perform add operation on stack, return next state
State add() {
    long arg1, arg2;
    if (stackPosition > 1) {
        arg1 = stack[--stackPosition];
        arg2 = stack[--stackPosition];
        stack[stackPosition++] = arg1 + arg2;
        printf(">> %ld + %ld is %ld\n", arg2, arg1, stack[stackPosition-1]);
        return BLANK;
    } else {
        printf("Insufficient operands for addition operation.\n");
        return EXIT;
    }
} 

// perform subtract operation on stack, return next state
State subtract() {
    long arg1, arg2;
    if (stackPosition > 1) {
        arg1 = stack[--stackPosition];
        arg2 = stack[--stackPosition];
        stack[stackPosition++] = arg2 - arg1;
        printf(">> %ld - %ld is %ld\n", arg2, arg1, stack[stackPosition-1]);
        return BLANK;
    } else {
        printf("Insufficient operands for subtraction operation.\n");
        return EXIT;
    }
}

// perform multiply operation on stack, return next state
State multiply() {
    long arg1, arg2;
    if (stackPosition > 1) {
        arg1 = stack[--stackPosition];
        arg2 = stack[--stackPosition];
        stack[stackPosition++] = arg2 * arg1;
        printf(">> %ld * %ld is %ld\n", arg2, arg1, stack[stackPosition-1]);
        return BLANK;
    } else {
        printf("Insufficient operands for multiplication operation.\n");
        return EXIT;
    }
}

// perform divide operation on stack, return next state
State divide() {
    long arg1, arg2;
    if (stackPosition > 1) {
        arg1 = stack[--stackPosition];
        arg2 = stack[--stackPosition];
        stack[stackPosition++] = arg2 / arg1;
        printf(">> %ld / %ld is %ld\n", arg2, arg1, stack[stackPosition-1]);
        return BLANK;
    } else {
        printf("Insufficient operands for division operation.\n");
        return EXIT;
    }
}
