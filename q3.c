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

    // extra redundant tokens
    IF,
    WHILE
} Token;

typedef int LABEL;
typedef char* VARIABLE;

typedef union {
    VARIABLE var;
    int ivalue;
} LexicalValue;

Token lookahead;
LexicalValue lexicalValue;

VARIABLE newtemp();
LABEL newlabel();
void label(LABEL);
void match(Token);
void error();

void gen(const char *format, ...);

typedef struct {
    LABEL cond_label;
    LABEL loop_label;
    LABEL finish_label;
    VARIABLE cond_var;
} Meta;

VARIABLE expression();

Meta meta() {
    return (Meta){
        .cond_label=newlabel(),
        .loop_label=newlabel(),
        .finish_label=newlabel(),
        .cond_var=newtemp(),
    };
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

    /* pseudo: gen(IASN counter initial_value) */
    gen("IASN %s %s\n", counter, initial_value);                    // counter = initial_value
    label(for_meta.cond_label);
    
    /* pseudo: gen(IGRT for_meta.cond_var counter max_value) */
    gen("IGRT %s %s %s\n", for_meta.cond_var, counter, max_value);  // cond_var = (counter > max_value)

    /* pseudo: gen(JUMPZ for_meta.loop_label for_meta.cond_var) */
    gen("JUMPZ L%d %s\n", for_meta.loop_label, for_meta.cond_var);  // if (!cond_var): loop

    /* pseudo: gen(JUMP for_meta.finish_label) */
    gen("JUMP L%d\n", for_meta.finish_label);                       // else: end loop
    label(for_meta.loop_label);

    match(SEMICOL);
    match(STEP);
    if (lookahead != NUM) error();
    int step = lexicalValue.ivalue;
    match(NUM);
    match(CLOSE_BRACKET);

    stmt();
    /* pseudo: gen(IADD counter counter step) */
    gen("IADD %s %s %d\n", counter, counter, step); // counter += step
    /* pseudo: gen(JUMP for_meta.cond_label) */
    gen("JUMP L%d\n", for_meta.cond_label);         // back to loop condition
    label(for_meta.finish_label);

    /* free VARIABLEs/LABELs if needed */
}
void stmt() {
    switch (lookahead) {
        case WHILE: /*...*/ break;
        case ID: /*...*/ break;
        case IF: /*...*/ break;
        case FOR_RANGE:
            for_range();
            return;
        
        /*...*/
    }
}

int main() {
    stmt();
    return 0;
}