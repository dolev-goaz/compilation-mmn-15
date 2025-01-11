#include "extern.h"
#include "lex.h"

extern Token lookahead;
extern LexicalValue lexicalValue;

void stmt();

typedef struct {
    LABEL cond_label;
    LABEL loop_label;
    LABEL finish_label;
    VARIABLE cond_var;
} Meta;

VARIABLE expression() {
    if (lookahead != NUM) error();
    VARIABLE output = newtemp();
    gen("IASN %s %d\n", output, lexicalValue.ivalue);
    match(NUM);
    return output;
}

Meta meta() {
    return (Meta){
        .cond_label=newlabel(),
        .loop_label=newlabel(),
        .finish_label=newlabel(),
        .cond_var=newtemp(),
    };
}

void free_meta(Meta m) {
    free(m.cond_var);
}

void for_range() {
    match(FOR_RANGE);
    match(OPEN_BRACKET);
    if (lookahead != ID) error();
    
    VARIABLE counter = lexicalValue.var;
    match(ID);
    match(EQ);

    VARIABLE initial_value = expression();
    match(TO);
    VARIABLE max_value = expression();

    Meta for_meta = meta();

    gen("IASN %s %s\n", counter, initial_value);
    label(for_meta.cond_label);
    gen("IGRT %s %s %s\n", for_meta.cond_var, counter, max_value);
    gen("JUMPZ L%d %s\n", for_meta.loop_label, for_meta.cond_var);
    gen("JUMP L%d\n", for_meta.finish_label);
    label(for_meta.loop_label);

    match(SEMICOL);
    match(STEP);
    if (lookahead != NUM) error();
    int step = lexicalValue.ivalue;
    match(NUM);
    match(CLOSE_BRACKET);

    stmt();
    gen("IADD %s %d\n", counter, step);
    gen("JUMP L%d\n", for_meta.cond_label);
    label(for_meta.finish_label);


    free(counter);
    free(initial_value);
    free(max_value);
    free_meta(for_meta);
}

void empty_stmt() {
    gen("**Empty statement**\n");
}

void stmt() {
    switch (lookahead) {
        case FOR_RANGE:
            for_range();
            return;
        default:
            empty_stmt();
            return;
    }
}

int main() {
    stmt();
    return 0;
}