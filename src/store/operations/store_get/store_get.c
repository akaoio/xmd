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

/**
 * @brief Get value from store
 * @param s Store instance
 * @param key Key to look up
 * @return Value or NULL if not found
 */
variable* store_get(store* s, const char* key) {
    if (!s || !key) {
        return NULL;
    }
    
    unsigned int index = xmd_hash_key(key, s->capacity);
    store_entry* entry = s->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}
