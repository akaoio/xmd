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
#include "../../../utils/common/common_macros.h"

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
    
    // Validate key is not empty
    if (strlen(key) == 0) {
        XMD_ERROR_RETURN(false, "store_set: Empty key provided");
    }
    
    if (value->type == VAR_STRING) {
    } else if (value->type == VAR_NUMBER) {
    }
    
    unsigned int index = xmd_hash_key(key, s->capacity);
    store_entry* entry = s->buckets[index];
    // Check if key already exists
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            variable_unref(entry->value);
            entry->value = value;
            variable_ref(value);
            return true;
        }
        entry = entry->next;
    }
    
    // Create new entry
    XMD_CREATE_VALIDATED(new_entry, store_entry, sizeof(store_entry), false);
    entry = new_entry;
    
    entry->key = xmd_strdup(key);
    if (!entry->key) {
        XMD_FREE_SAFE(entry);
        return false;
    }
    
    entry->value = value;
    variable_ref(value);
    entry->next = s->buckets[index];
    s->buckets[index] = entry;
    s->size++;
    return true;
}
