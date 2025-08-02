/**
 * @file store_remove.c
 * @brief Implementation of store_remove function
 * 
 * This file contains ONLY the store_remove function.
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
#include "variable.h"

/**
 * @brief Simple hash function (static helper for store_remove)
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
 * @brief Remove key from store
 */
bool store_remove(store* s, const char* key) {
    if (!s || !key) {
        return false;
    }
    
    unsigned int index = hash_key(key) % s->capacity;
    store_entry* entry = s->buckets[index];
    store_entry* prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                s->buckets[index] = entry->next;
            }
            
            free(entry->key);
            variable_unref(entry->value);
            free(entry);
            s->size--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return false;
}