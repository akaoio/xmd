/**
 * @file variable_to_string.h
 * @brief Declaration for variable_to_string function
 * 
 * This file contains ONLY the variable_to_string declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_TO_STRING_H
#define VARIABLE_TO_STRING_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
char* variable_to_string(const variable* var);

#endif /* VARIABLE_TO_STRING_H */
