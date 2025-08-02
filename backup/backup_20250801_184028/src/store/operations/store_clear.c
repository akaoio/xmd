/**
 * @file store_clear.c
 * @brief Implementation of store_clear function
 * 
 * This file contains ONLY the store_clear function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include <stdlib.h>

#include "store.h"
#include "store_internal.h"
#include "store_internal.h"
#include "variable.h"

/**
 * @brief Clear all entries from store
 */

/**
 * @brief Clear all entries from store
 */
void store_clear(store* s) {
    if (!s) {
        return;
    }
    
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry) {
            store_entry* next = entry->next;
            free(entry->key);
            variable_unref(entry->value);
            free(entry);
            entry = next;
        }
        s->buckets[i] = NULL;
    }
    
    s->size = 0;
}