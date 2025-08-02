/**
 * @file variable_get_string.h
 * @brief Declaration for variable_get_string function
 * 
 * This file contains ONLY the variable_get_string declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_GET_STRING_H
#define VARIABLE_GET_STRING_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
const char* variable_get_string(const variable* var);

#endif /* VARIABLE_GET_STRING_H */
