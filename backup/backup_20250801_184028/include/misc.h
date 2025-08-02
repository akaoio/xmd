/**
 * @file misc.h
 * @brief Forward declarations for misc module functions
 * 
 * Auto-generated during modular refactoring.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_MISC_H
#define XMD_MISC_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used in this module */

/* Function declarations */
static unsigned int hash_key(const char* key);
variable*variable_convert(variable* var, variable_type target_type);
bool variable_extended(variable* var);

#endif /* XMD_MISC_H */
