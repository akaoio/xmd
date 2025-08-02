/**
 * @file variable_unref.h
 * @brief Declaration for variable_unref function
 * 
 * This file contains ONLY the variable_unref declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_UNREF_H
#define VARIABLE_UNREF_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
void variable_unref(variable* var);

#endif /* VARIABLE_UNREF_H */
