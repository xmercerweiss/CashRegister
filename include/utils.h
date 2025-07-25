#include <stdlib.h>
#include <stdio.h>

#include "meta.h"


#ifndef UTILS_H
#define UTILS_H

// Custom Data Types
typedef unsigned long Currency;
typedef unsigned short Percentage;

// Aliases for Existing Types
typedef unsigned long  uint64;
typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

// Macros
#define ERROR(msg) fprintf(stderr, "%s: %s\n", PROGRAM_TITLE, msg); exit(1)

#endif
