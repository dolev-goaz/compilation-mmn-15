#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

typedef int LABEL;
typedef char* VARIABLE;

VARIABLE newtemp();
LABEL newlabel();

void gen(const char *format, ...);
void label(LABEL);

void error();