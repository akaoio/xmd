/**
 * @file variable_copy.h
 * @brief Declaration for variable_copy function
 * 
 * This file contains ONLY the variable_copy declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_COPY_H
#define VARIABLE_COPY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_copy(const variable* var);

#endif /* VARIABLE_COPY_H */
