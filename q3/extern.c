#include "extern.h"

static int label_count = 1;
static int var_count = 1;

void error() {
    fprintf(stderr, "Error while parsing");
}

LABEL newlabel() {
    return label_count++;
}

VARIABLE newtemp() {
    int len = var_count <= 1? 1: ceil(log10(var_count));
    VARIABLE out = (char*)malloc(len + 2);

    // out[0] = 't';
    sprintf(out, "t%d", var_count);
    var_count+=1;
    return out;
}

void gen(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}

void label(LABEL l) {
    printf("L%d:\n", l);
}