/**
 * @file store_ops.c
 * @brief Store operations implementation
 * @author XMD Team
 *
 * Implementation of store query and manipulation operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "store.h"
#include "variable.h"
#include "../../../include/utils.h"

/**
 * @struct store_entry
 * @brief Store entry for key-value pairs (redefined for access)
 */
typedef struct store_entry {
    char* key;                     /**< Variable name (owned) */
    variable* value;               /**< Variable value (referenced) */
    struct store_entry* next;      /**< Next entry in collision chain */
} store_entry;

/**
 * @struct store
 * @brief Variable storage container (redefined for access)
 */
struct store {
    store_entry** buckets;         /**< Hash table buckets */
    size_t capacity;               /**< Current capacity */
    size_t size;                   /**< Number of stored variables */
};

// hash_key function moved to utils.c as xmd_hash_key

// store_get moved to store.c to consolidate implementation

/**
 * @brief Check if variable exists in store
 * @param s Store instance
 * @param name Variable name
 * @return true if variable exists, false otherwise
 */
bool store_has(store* s, const char* name) {
    return store_get(s, name) != NULL;
}

/**
 * @brief Remove a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return true if removed, false if not found
 */
bool store_remove(store* s, const char* name) {
    if (s == NULL || name == NULL) {
        return false;
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    store_entry* entry = s->buckets[hash];
    store_entry* prev = NULL;
    
    while (entry != NULL) {
        if (strcmp(entry->key, name) == 0) {
            // Remove entry from chain
            if (prev != NULL) {
                prev->next = entry->next;
            } else {
                s->buckets[hash] = entry->next;
            }
            
            // Free entry
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

/**
 * @brief Clear all variables from store
 * @param s Store instance
 */
void store_clear(store* s) {
    if (s == NULL) {
        return;
    }
    
    // Free all entries
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL) {
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

/**
 * @brief Get number of variables in store
 * @param s Store instance
 * @return Number of variables
 */
size_t store_size(store* s) {
    if (s == NULL) {
        return 0;
    }
    
    return s->size;
}

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