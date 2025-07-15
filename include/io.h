#include <stdio.h>

#include "utils.h"


#ifndef IO_H
#define IO_H

#define MAX_BUFFER_SIZE  128

#define CURRENCY_SYM "$"

char *sprint_currency(char*, size_t, char*, Currency);
FILE *fprint_currency(FILE*, char*, Currency);
void print_currency(char*, currency);

#endif
