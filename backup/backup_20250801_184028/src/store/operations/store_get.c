/**
 * @file store_get.c
 * @brief Implementation of store_get function
 * 
 * This file contains ONLY the store_get function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include <string.h>

#include "store.h"
#include "store_internal.h"
#include "store_internal.h"
#include "variable.h"

/**
 * @brief Simple hash function (static helper for store_get)
 */
static unsigned int hash_key(const char* key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/**
 * @brief Get value from store
 */
variable* store_get(store* s, const char* key) {
    if (!s || !key) {
        return NULL;
    }
    
    unsigned int index = hash_key(key) % s->capacity;
    store_entry* entry = s->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}