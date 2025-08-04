/**
 * @file store_get.c
 * @brief Implementation of store_get function
 * 
 * This file contains ONLY the store_get function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <string.h>
#include "store.h"
#include "store_internal.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Get value from store
 * @param s Store instance
 * @param key Key to look up
 * @return Value or NULL if not found
 */
variable* store_get(store* s, const char* key) {
    XMD_NULL_CHECK(s, NULL);
    XMD_NULL_CHECK(key, NULL);
    
    XMD_VALIDATE_KEY_NOT_EMPTY(key, NULL, "store_get");
    
    XMD_HASH_TABLE_FIND_ENTRY(s, key, entry, return entry->value);
    
    // Key not found - provide detailed error
    XMD_ERROR_RETURN(NULL, "store_get: Key '%s' not found in store", key);
}
