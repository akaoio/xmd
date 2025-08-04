/**
 * @file store_has.c
 * @brief Implementation of store_has function
 * 
 * This file contains ONLY the store_has function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdbool.h>
#include "../../../../include/store.h"
#include "../../../../include/store_internal.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Check if store has key
 */
bool store_has(store* s, const char* key) {
    XMD_NULL_CHECK(s, false);
    XMD_NULL_CHECK(key, false);
    
    XMD_VALIDATE_KEY_NOT_EMPTY(key, false, "store_has");
    
    return store_get(s, key) != NULL;
}
