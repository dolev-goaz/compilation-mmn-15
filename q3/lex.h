#pragma once
#include <string.h>
#include "extern.h"

typedef enum {
    ID = 1,
    FOR_RANGE,
    TO,
    STEP,
    NUM,

    OPEN_BRACKET,
    CLOSE_BRACKET,
    EQ,
    SEMICOL,
} Token;

void match(Token);

typedef union {
    VARIABLE var;
    int ivalue;
} LexicalValue;