/**
 * @file store_has.c
 * @brief Implementation of store_has function
 * 
 * This file contains ONLY the store_has function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include <stdbool.h>

#include "store.h"
#include "store_internal.h"
#include "store_internal.h"

/**
 * @brief Check if store has key
 */

/**
 * @brief Check if store has key
 */
bool store_has(store* s, const char* key) {
    return store_get(s, key) != NULL;
}