#include "lex.h"

Token lookahead;
Token lookaheads[] = {
    FOR_RANGE,
    OPEN_BRACKET,
    ID,
    EQ,
    NUM,
    TO,
    NUM,
    SEMICOL,
    STEP,
    NUM,
    CLOSE_BRACKET,
};

int lookahead_index = 0;
looahead = FOR_RANGE; // lookaheads[0]
LexicalValue lexicalValue;

void match(enum Token token) {
    if (lookahead != token) {
        error();
    }
    lookahead = lookaheads[++lookahead_index];
    if (lookahead == ID) {
        lexicalValue.var = (char*)malloc(8); // strlen("counter")+1
        strncpy(lexicalValue.var, "counter", 7);
        lexicalValue.var[7] = 0;
    } else if (lookahead == NUM) {
        lexicalValue.ivalue = lookahead_index * 5;
    }
}