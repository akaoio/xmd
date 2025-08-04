/**
 * @file store_set.c
 * @brief Implementation of store_set function
 * 
 * This file contains ONLY the store_set function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/store.h"
#include "../../../../include/store_internal.h"
#include "../../../../include/utils.h"
#include "../../../../include/variable.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Set value in store
 * @param s Store instance
 * @param key Key to set
 * @param value Value to set
 * @return true on success, false on error
 */
bool store_set(store* s, const char* key, variable* value) {
    XMD_NULL_CHECK(s, false);
    XMD_NULL_CHECK(key, false);
    XMD_NULL_CHECK(value, false);
    
    XMD_VALIDATE_KEY_NOT_EMPTY(key, false, "store_set");
    
    if (value->type == VAR_STRING) {
    } else if (value->type == VAR_NUMBER) {
    }
    
    unsigned int index = xmd_hash_key(key, s->capacity);
    XMD_HASH_TABLE_FIND_ENTRY(s, key, entry, {
        XMD_VARIABLE_REPLACE(entry, value);
        return true;
    });
    
    // Create new entry using store macro
    store_entry* new_entry;
    XMD_CREATE_STORE_ENTRY(new_entry, key, value, false);
    new_entry->next = s->buckets[index];
    s->buckets[index] = new_entry;
    s->size++;
    return true;
}
