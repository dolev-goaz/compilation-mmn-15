#include "extern.h"

static int label_count = 0;
static int var_count = 0;

void error() {
    fprintf(stderr, "Error while parsing");
}

LABEL newlabel() {
    return label_count++;
}

VARIABLE newtemp() {
    int len = ceil(log10(var_count));
    VARIABLE out = (char*)malloc(len + 2);
    snprintf(out, len+1, "t%d", var_count++);
    out[len+1] = 0;
    return out;
}

void gen(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}

void label(LABEL l) {
    printf("%d:\n", l);
}