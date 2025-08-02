/**
 * @file variable_new_array.h
 * @brief Declaration for variable_new_array function
 * 
 * This file contains ONLY the variable_new_array declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_NEW_ARRAY_H
#define VARIABLE_NEW_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_new_array(variable** items, size_t count);

#endif /* VARIABLE_NEW_ARRAY_H */
