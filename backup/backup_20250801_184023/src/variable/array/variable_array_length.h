/**
 * @file variable_array_length.h
 * @brief Declaration for variable_array_length function
 * 
 * This file contains ONLY the variable_array_length declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_ARRAY_LENGTH_H
#define VARIABLE_ARRAY_LENGTH_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
size_t variable_array_length(const variable* var);

#endif /* VARIABLE_ARRAY_LENGTH_H */
