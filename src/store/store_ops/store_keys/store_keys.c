/**
 * @file store_keys.c
 * @brief Get all variable names
 * @author XMD Team
 */

#include "../../../../include/store_ops_internal.h"

/**
 * @brief Get all variable names
 * @param s Store instance
 * @param count Output parameter for array size
 * @return Array of variable names (must be freed)
 */
char** store_keys(store* s, size_t* count) {
    if (s == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }
    
    if (s->size == 0) {
        *count = 0;
        return NULL;
    }
    
    // Allocate array for keys
    char** keys = malloc(s->size * sizeof(char*));
    if (keys == NULL) {
        *count = 0;
        return NULL;
    }
    
    size_t key_index = 0;
    
    // Collect all keys
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL) {
            // Copy key
            size_t key_len = strlen(entry->key);
            keys[key_index] = malloc(key_len + 1);
            if (keys[key_index] == NULL) {
                // Free already allocated keys
                for (size_t j = 0; j < key_index; j++) {
                    free(keys[j]);
                }
                free(keys);
                *count = 0;
                return NULL;
            }
            strcpy(keys[key_index], entry->key);
            key_index++;
            
            entry = entry->next;
        }
    }
    
    *count = s->size;
    return keys;
}