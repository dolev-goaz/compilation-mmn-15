#include "lex.h"

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
Token lookahead = FOR_RANGE; // lookaheads[0]
LexicalValue lexicalValue;

void match(Token token) {
    if (lookahead != token) {
        error();
    }
    lookahead = lookaheads[++lookahead_index];
    if (lookahead == ID) {
        lexicalValue.var = (char*)malloc(8); // strlen("counter")+1
        strncpy(lexicalValue.var, "counter", 8);
    } else if (lookahead == NUM) {
        lexicalValue.ivalue = (lookahead_index * 5) % 20;
    }
}