/**
 * @file store_remove.h
 * @brief Declaration for store_remove function
 * 
 * This file contains ONLY the store_remove declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef STORE_REMOVE_H
#define STORE_REMOVE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

/* Function declaration */
bool store_remove(store* s, const char* name);

#endif /* STORE_REMOVE_H */
