/**
 * @file store_set.c
 * @brief Implementation of store_set function
 * 
 * This file contains ONLY the store_set function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "store.h"
#include "store_internal.h"
#include "store_internal.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Simple hash function (static helper for store_set)
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
 * @brief Set value in store
 */
bool store_set(store* s, const char* key, variable* value) {
    if (!s || !key || !value) {
        return false;
    }
    
    unsigned int index = hash_key(key) % s->capacity;
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
    entry = xmd_malloc(sizeof(store_entry));
    if (!entry) {
        return false;
    }
    
    entry->key = xmd_strdup(key);
    entry->value = value;
    variable_ref(value);
    entry->next = s->buckets[index];
    s->buckets[index] = entry;
    s->size++;
    
    return 0;
}