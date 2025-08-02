/**
 * @file variable_array_size.h
 * @brief Declaration for variable_array_size function
 * 
 * This file contains ONLY the variable_array_size declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_ARRAY_SIZE_H
#define VARIABLE_ARRAY_SIZE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
size_t variable_array_size(const variable* array_var);

#endif /* VARIABLE_ARRAY_SIZE_H */
