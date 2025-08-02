/**
 * @file store_keys.c
 * @brief Implementation of store_keys function
 * 
 * This file contains ONLY the store_keys function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include <stddef.h>
#include <stdlib.h>

#include "store.h"
#include "store_internal.h"
#include "store_internal.h"
#include "utils.h"

/**
 * @brief Get all keys from store
 * @param s Store
 * @param count Output count of keys
 * @return Array of key strings or NULL
 */

/**
 * @brief Get all keys from store
 * @param s Store
 * @param count Output count of keys
 * @return Array of key strings or NULL
 */
char** store_keys(store* s, size_t* count) {
    if (!s || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    // Count keys first
    size_t key_count = 0;
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry) {
            key_count++;
            entry = entry->next;
        }
    }
    
    if (key_count == 0) {
        *count = 0;
        return NULL;
    }
    
    // Allocate array
    char** keys = xmd_malloc(key_count * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    // Fill array
    size_t idx = 0;
    for (size_t i = 0; i < s->capacity && idx < key_count; i++) {
        store_entry* entry = s->buckets[i];
        while (entry && idx < key_count) {
            keys[idx] = xmd_strdup(entry->key);
            idx++;
            entry = entry->next;
        }
    }
    
    *count = key_count;
    return keys;
}