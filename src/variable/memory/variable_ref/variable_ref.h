/**
 * @file variable_ref.h
 * @brief Declaration for variable_ref function
 * 
 * This file contains ONLY the variable_ref declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef VARIABLE_REF_H
#define VARIABLE_REF_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct variable variable;

/* Function declaration */
variable* variable_ref(variable* var);

#endif /* VARIABLE_REF_H */
