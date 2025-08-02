/**
 * @file store_has.h
 * @brief Declaration for store_has function
 * 
 * This file contains ONLY the store_has declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef STORE_HAS_H
#define STORE_HAS_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

/* Function declaration */
bool store_has(store* s, const char* name);

#endif /* STORE_HAS_H */
