#include <stdio.h>

#include "utils.h"


#ifndef IO_H
#define IO_H

// *** Constants 
#define MAX_BUFFER_SIZE 128
#define MIN_BUFFER_SIZE  32

#define CURRENCY_SYM "$"

// *** Public Interface
// Currency IO
char *sprint_currency(char*, size_t, char*, Currency);
FILE *fprint_currency(FILE*, char*, Currency);
void print_currency(char*, Currency);
Currency sscan_currency(char*);
Currency fscan_currency(FILE*);
Currency scan_currency(void);

// Percentage IO
char *sprint_percent(char*, size_t, char*, Percent);
FILE *fprint_percent(FILE*, char*, Percent);
void print_percent(char*, Percent);
Percent sscan_percent(char*);
Percent fscan_percent(FILE*);
Percent scan_percent(void);

#endif
