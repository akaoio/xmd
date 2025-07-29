#ifndef DEBUG_TRACE_H
#define DEBUG_TRACE_H

#ifdef DEBUG_AST
#include <stdio.h>
#define DEBUG_PRINT(...) fprintf(stderr, "[DEBUG] " __VA_ARGS__)
#else
#define DEBUG_PRINT(...) 
#endif

#endif