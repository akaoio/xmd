/**
 * @file store_remove.c
 * @brief Implementation of store_remove function
 * 
 * This file contains ONLY the store_remove function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/store.h"
#include "../../../../include/store_internal.h"
#include "../../../../include/variable.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Remove key from store
 * @param s Store instance
 * @param key Key to remove
 * @return true if removed, false if not found
 */
bool store_remove(store* s, const char* key) {
    XMD_NULL_CHECK(s, false);
    XMD_NULL_CHECK(key, false);
    
    // Validate key is not empty
    if (strlen(key) == 0) {
        XMD_ERROR_RETURN(false, "store_remove: Empty key provided");
    }
    
    unsigned int index = xmd_hash_key(key, s->capacity);
    store_entry* entry = s->buckets[index];
    store_entry* prev = NULL;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                s->buckets[index] = entry->next;
            }
            
            XMD_FREE_SAFE(entry->key);
            variable_unref(entry->value);
            XMD_FREE_SAFE(entry);
            s->size--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    return false;
}
