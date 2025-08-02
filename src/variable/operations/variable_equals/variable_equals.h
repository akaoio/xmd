/**
 * @file variable_equals.h
 * @brief Declaration for variable_equals function
 * 
 * This file contains ONLY the variable_equals declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_EQUALS_H
#define VARIABLE_EQUALS_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
bool variable_equals(const variable* a, const variable* b);

#endif /* VARIABLE_EQUALS_H */
