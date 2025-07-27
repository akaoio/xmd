#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file store_keys.c
 * @brief Store keys enumeration function
 * @author XMD Team
 *
 * Implementation of key enumeration for the XMD store system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/store.h"
#include "../../../include/store_internal.h"

/**
 * @brief Get all variable names
 * @param s Store instance
 * @param count Output parameter for array size
 * @return Array of variable names (must be freed)
 */
char** store_keys(store* s, size_t* count) {
    if (s == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }
    
    if (s->size == 0) {
        *count = 0;
        return NULL;
    }
    
    char** keys = malloc(s->size * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    size_t key_index = 0;
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL && key_index < s->size) {
            keys[key_index] = strdup(entry->key);
            key_index++;
            entry = entry->next;
        }
    }
    
    *count = key_index;
    return keys;
}