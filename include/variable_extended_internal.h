/**
 * @file variable_extended_internal.h
 * @brief Internal declarations for extended variable functions
 * @author XMD Team
 */

#ifndef VARIABLE_EXTENDED_INTERNAL_H
#define VARIABLE_EXTENDED_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/variable.h"

// Function prototypes
bool variable_get_boolean(const variable* var);
double variable_get_number(const variable* var);
const char* variable_get_string(const variable* var);

#endif /* VARIABLE_EXTENDED_INTERNAL_H */