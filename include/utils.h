#include <stdlib.h>
#include <stdio.h>

#include "meta.h"


#ifndef UTILS_H
#define UTILS_H

// *** Type Definitions
// Custom
typedef unsigned long Currency;
typedef unsigned int Percent;

// Aliased
typedef unsigned long  uint64;
typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;


// *** Macros
// Error Handling
#define ERROR(msg) fprintf(stderr, "%s: %s\n", PROGRAM_TITLE, msg); exit(1)  // Fatal Errors
#define NONF_ERROR(msg) fprintf(stderr, "%s\n", msg)  // Non-fatal Errors

#endif
