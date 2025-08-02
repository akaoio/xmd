/**
 * @file store_set.h
 * @brief Declaration for store_set function
 * 
 * This file contains ONLY the store_set declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef STORE_SET_H
#define STORE_SET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

/* Function declaration */
bool store_set(store* s, const char* name, variable* var);

#endif /* STORE_SET_H */
