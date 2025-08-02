/**
 * @file store_get.h
 * @brief Declaration for store_get function
 * 
 * This file contains ONLY the store_get declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef STORE_GET_H
#define STORE_GET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

/* Function declaration */
variable* store_get(store* s, const char* name);

#endif /* STORE_GET_H */
