/**
 * @file store_size.c
 * @brief Implementation of store_size function
 * 
 * This file contains ONLY the store_size function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include <stddef.h>

#include "store.h"
#include "store_internal.h"

/**
 * @brief Get store size
 */

/**
 * @brief Get store size
 */
size_t store_size(store* s) {
    return s ? s->size : 0;
}