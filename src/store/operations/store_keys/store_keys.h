/**
 * @file store_keys.h
 * @brief Declaration for store_keys function
 * 
 * This file contains ONLY the store_keys declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef STORE_KEYS_H
#define STORE_KEYS_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

/* Function declaration */
char** store_keys(store* s, size_t* count);

#endif /* STORE_KEYS_H */
