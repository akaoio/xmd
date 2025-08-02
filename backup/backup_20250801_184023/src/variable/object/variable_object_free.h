/**
 * @file variable_object_free.h
 * @brief Declaration for variable_object_free function
 * 
 * This file contains ONLY the variable_object_free declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_OBJECT_FREE_H
#define VARIABLE_OBJECT_FREE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
voidvariable_object_free(variable* object_var);

#endif /* VARIABLE_OBJECT_FREE_H */
